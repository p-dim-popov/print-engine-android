/* print-engine-android
   Copyright (C) 2026 Petar Popov

   A reader of PWG Raster streams (PWG 5102.4); see pwg-raster.h.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include "pwg-raster.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE 1796
#define COLOR_SPACE_SGRAY 18
#define COLOR_SPACE_SRGB 19
/* Larger pages than this are refused, not allocated: 2 m at 2400 dpi. */
#define MAX_PIXELS 200000u

struct pwg_reader
{
  FILE *in;
  int started;              /* sync word read */
  int in_page;              /* a page header was read */
  pwg_page_t page;
  size_t line_bytes;
  unsigned lines_left;      /* lines of the page not yet returned */
  unsigned repeat;          /* times the decoded line is still to be returned */
  unsigned char *decoded;   /* the line being repeated */
  char error[160];
};

static int
fail(pwg_reader_t *r, const char *message)
{
  snprintf(r->error, sizeof r->error, "%s", message);
  return -1;
}

static uint32_t
be32(const unsigned char *p)
{
  return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
}

pwg_reader_t *
pwg_reader_open(FILE *in)
{
  pwg_reader_t *r = calloc(1, sizeof *r);
  if (r)
    r->in = in;
  return r;
}

void
pwg_reader_close(pwg_reader_t *r)
{
  if (r)
    free(r->decoded);
  free(r);
}

const char *
pwg_reader_error(const pwg_reader_t *r)
{
  return r->error;
}

/* Decodes one line record: the line-repeat byte, then runs of pixels. */
static int
decode_line(pwg_reader_t *r)
{
  int repeat = getc(r->in);
  if (repeat == EOF)
    return fail(r, "the page ends before its last line");
  unsigned bpp = r->page.channels;
  size_t at = 0;
  while (at < r->line_bytes)
    {
      int code = getc(r->in);
      if (code == EOF)
        return fail(r, "the page ends inside a line");
      if (code == 128)
        {
          /* The rest of the line is white. */
          memset(r->decoded + at, 0xff, r->line_bytes - at);
          at = r->line_bytes;
        }
      else if (code < 128)
        {
          size_t bytes = (size_t)(code + 1) * bpp;
          if (bytes > r->line_bytes - at)
            return fail(r, "a run goes past the end of its line");
          if (fread(r->decoded + at, 1, bpp, r->in) != bpp)
            return fail(r, "the page ends inside a line");
          for (size_t i = bpp; i < bytes; i++)
            r->decoded[at + i] = r->decoded[at + i - bpp];
          at += bytes;
        }
      else
        {
          size_t bytes = (size_t)(257 - code) * bpp;
          if (bytes > r->line_bytes - at)
            return fail(r, "a run goes past the end of its line");
          if (fread(r->decoded + at, 1, bytes, r->in) != bytes)
            return fail(r, "the page ends inside a line");
          at += bytes;
        }
    }
  r->repeat = (unsigned)repeat + 1;
  return 0;
}

/* Makes the decoded line the next one of the page, decoding the next line
   record once the current one has repeated its last time. */
static int
next_record(pwg_reader_t *r)
{
  if (r->repeat == 0 && decode_line(r) != 0)
    return -1;
  if (r->repeat > r->lines_left)
    return fail(r, "a line repeats past the end of its page");
  return 0;
}

int
pwg_read_line(pwg_reader_t *r, unsigned char *line)
{
  if (!r->in_page || r->lines_left == 0)
    return fail(r, "no line left on the page");
  if (next_record(r) != 0)
    return -1;
  memcpy(line, r->decoded, r->line_bytes);
  r->repeat--;
  r->lines_left--;
  return 0;
}

static int
parse_header(pwg_reader_t *r, const unsigned char *h)
{
  pwg_page_t *p = &r->page;
  memset(p, 0, sizeof *p);
  uint32_t bits_per_color = be32(h + 384);
  uint32_t bits_per_pixel = be32(h + 388);
  uint32_t bytes_per_line = be32(h + 392);
  uint32_t color_order = be32(h + 396);
  uint32_t color_space = be32(h + 400);
  uint32_t num_colors = be32(h + 420);
  p->x_dpi = be32(h + 276);
  p->y_dpi = be32(h + 280);
  p->page_width = be32(h + 352);
  p->page_height = be32(h + 356);
  p->width = be32(h + 372);
  p->height = be32(h + 376);

  if (color_space == COLOR_SPACE_SGRAY && num_colors == 1)
    p->channels = 1;
  else if (color_space == COLOR_SPACE_SRGB && num_colors == 3)
    p->channels = 3;
  else
    return fail(r, "the page is neither sgray_8 nor srgb_8");
  if (bits_per_color != 8 || bits_per_pixel != 8 * p->channels)
    return fail(r, "the page is neither sgray_8 nor srgb_8");
  if (color_order != 0)
    return fail(r, "the page's colours are not chunky");
  if (p->x_dpi == 0 || p->y_dpi == 0)
    return fail(r, "the page has no resolution");
  if (p->width == 0 || p->height == 0 || p->width > MAX_PIXELS || p->height > MAX_PIXELS)
    return fail(r, "the page's size in pixels is out of range");
  if (bytes_per_line != p->width * p->channels)
    return fail(r, "the page's bytes per line do not match its width");
  memcpy(p->media_name, h + 1732, 64);
  p->media_name[64] = '\0';

  r->line_bytes = bytes_per_line;
  r->lines_left = p->height;
  r->repeat = 0;
  unsigned char *decoded = realloc(r->decoded, r->line_bytes);
  if (!decoded)
    return fail(r, "out of memory");
  r->decoded = decoded;
  return 0;
}

int
pwg_next_page(pwg_reader_t *r, pwg_page_t *page)
{
  if (!r->started)
    {
      unsigned char sync[4];
      size_t got = fread(sync, 1, 4, r->in);
      if (got != 4 || memcmp(sync, "RaS2", 4) != 0)
        return fail(r, "the input does not start with the PWG Raster sync word RaS2");
      r->started = 1;
    }
  while (r->in_page && r->lines_left > 0)
    {
      if (next_record(r) != 0)
        return -1;
      r->lines_left -= r->repeat;
      r->repeat = 0;
    }
  r->in_page = 0;

  unsigned char header[HEADER_SIZE];
  size_t got = fread(header, 1, HEADER_SIZE, r->in);
  if (got == 0 && feof(r->in))
    return 0;
  if (got != HEADER_SIZE)
    return fail(r, "the input ends inside a page header");
  if (parse_header(r, header) != 0)
    return -1;
  r->in_page = 1;
  *page = r->page;
  return 1;
}
