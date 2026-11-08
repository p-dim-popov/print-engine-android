/* print-engine-android
   Copyright (C) 2026 Petar Popov

   A reader of PWG Raster streams (PWG 5102.4): the sync word, then per
   page a 1796-byte header and the page's run-length coded lines. It takes
   8-bit sGray and 8-bit sRGB pages, chunky, and refuses everything else.

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

#ifndef PWG_RASTER_H
#define PWG_RASTER_H

#include <stddef.h>
#include <stdio.h>

typedef struct
{
  unsigned width;           /* pixels per line */
  unsigned height;          /* lines */
  unsigned x_dpi, y_dpi;    /* HWResolution */
  unsigned page_width;      /* PageSize, points */
  unsigned page_height;
  unsigned channels;        /* 1: sgray_8, 3: srgb_8 */
  char media_name[65];      /* PageSizeName, may be empty */
} pwg_page_t;

typedef struct pwg_reader pwg_reader_t;

/* A reader of the stream on in; NULL when out of memory. */
pwg_reader_t *pwg_reader_open(FILE *in);
void pwg_reader_close(pwg_reader_t *reader);

/* Reads the next page header: 1 with *page filled, 0 at the end of the
   stream, -1 on an error (pwg_reader_error says which). The first call
   also reads the sync word. Lines of the previous page that were not read
   are skipped first. */
int pwg_next_page(pwg_reader_t *reader, pwg_page_t *page);

/* Reads the next line of the current page into line, width * channels
   bytes: 0, or -1 on an error or when the page has no more lines. */
int pwg_read_line(pwg_reader_t *reader, unsigned char *line);

/* The last error, in words. */
const char *pwg_reader_error(const pwg_reader_t *reader);

#endif
