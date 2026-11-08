/* print-engine-android
   Copyright (C) 2026 Petar Popov

   print-engine: a printer driver program over Gutenprint. `describe`
   lists a driver's papers, resolutions and colour modes; `print` turns
   one PWG Raster stream on stdin into the printer's own bytes on stdout.
   README.md states the interface.

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

#include <gutenprint/gutenprint.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pwg-media.h"
#include "pwg-raster.h"

#define EXIT_USAGE 2
#define EXIT_BAD_RASTER 3
#define EXIT_DRIVER_FAILED 4

static const char usage_text[] =
  "usage: print-engine describe --driver NAME\n"
  "       print-engine print --driver NAME [--option KEY=VALUE]...\n"
  "\n"
  "describe writes the driver's choices as KEY=VALUE lines on stdout.\n"
  "print reads one PWG Raster stream (sgray_8 or srgb_8) on stdin and writes\n"
  "the printer's bytes on stdout. Options: media=PWG-NAME,\n"
  "resolution=Ndpi or XxYdpi, color-mode=color or monochrome.\n"
  "STP_DATA_PATH names Gutenprint's data directory.\n"
  "Exit codes: 0 success, 2 usage or unknown driver, 3 bad raster,\n"
  "4 driver or output failure.\n";

static int
usage_error(const char *message, const char *detail)
{
  if (message)
    fprintf(stderr, "print-engine: %s%s\n", message, detail ? detail : "");
  fputs(usage_text, stderr);
  return EXIT_USAGE;
}

static void
write_stderr(void *data, const char *buffer, size_t bytes)
{
  (void)data;
  fwrite(buffer, 1, bytes, stderr);
}

/* ---- The driver's choices ---------------------------------------------- */

typedef struct
{
  char *paper;          /* Gutenprint PageSize name */
  char pwg[128];        /* its PWG media name */
} paper_t;

typedef struct
{
  const char *name;     /* Gutenprint Resolution choice, NULL for none */
  int x_dpi, y_dpi;
  int color, mono;      /* PrintingMode offers Color, BW */
} mode_t_;

typedef struct
{
  const stp_printer_t *printer;
  stp_vars_t *defaults;
  paper_t *papers;
  size_t paper_count;
  const char *default_paper;
  mode_t_ *modes;
  size_t mode_count;
  stp_parameter_t resolutions;   /* owns the mode names */
  int has_resolutions;
  int default_x_dpi, default_y_dpi;
  int default_color;             /* 1 Color, 0 BW */
} driver_t;

static int
string_list_has(const stp_string_list_t *list, const char *name)
{
  return list && name && stp_string_list_is_present(list, name);
}

static void
printing_modes(const stp_vars_t *v, int *color, int *mono)
{
  stp_parameter_t desc;
  stp_describe_parameter(v, "PrintingMode", &desc);
  *color = desc.p_type == STP_PARAMETER_TYPE_STRING_LIST && string_list_has(desc.bounds.str, "Color");
  *mono = desc.p_type == STP_PARAMETER_TYPE_STRING_LIST && string_list_has(desc.bounds.str, "BW");
  stp_parameter_description_destroy(&desc);
}

static const paper_t *
paper_by_pwg(const driver_t *d, const char *pwg)
{
  for (size_t i = 0; i < d->paper_count; i++)
    if (strcmp(d->papers[i].pwg, pwg) == 0)
      return &d->papers[i];
  return NULL;
}

static const paper_t *
paper_by_name(const driver_t *d, const char *name)
{
  for (size_t i = 0; i < d->paper_count; i++)
    if (strcmp(d->papers[i].paper, name) == 0)
      return &d->papers[i];
  return NULL;
}

static void
load_papers(driver_t *d)
{
  stp_parameter_t desc;
  stp_describe_parameter(d->defaults, "PageSize", &desc);
  size_t count = desc.p_type == STP_PARAMETER_TYPE_STRING_LIST && desc.bounds.str
    ? stp_string_list_count(desc.bounds.str) : 0;
  d->papers = calloc(count ? count : 1, sizeof *d->papers);
  for (size_t i = 0; i < count; i++)
    {
      const char *name = stp_string_list_param(desc.bounds.str, i)->name;
      const stp_papersize_t *size = stp_describe_papersize(d->defaults, name);
      /* Custom sizes and rolls have no fixed size: skip them. */
      if (!size || size->width <= 0 || size->height <= 0)
        continue;
      int metric = size->paper_unit == PAPERSIZE_METRIC_STANDARD
        || size->paper_unit == PAPERSIZE_METRIC_EXTENDED;
      paper_t paper;
      pwg_media_name(name, size->width, size->height, metric, paper.pwg, sizeof paper.pwg);
      /* Papers of one size share a name; the first of them stands for it. */
      if (paper_by_pwg(d, paper.pwg))
        continue;
      paper.paper = strdup(name);
      d->papers[d->paper_count++] = paper;
    }
  const char *deflt = desc.deflt.str;
  d->default_paper = NULL;
  if (deflt && paper_by_name(d, deflt))
    d->default_paper = paper_by_name(d, deflt)->pwg;
  else if (d->paper_count > 0)
    d->default_paper = d->papers[0].pwg;
  stp_parameter_description_destroy(&desc);
}

static void
load_modes(driver_t *d)
{
  stp_describe_parameter(d->defaults, "Resolution", &d->resolutions);
  size_t count = 0;
  d->has_resolutions = d->resolutions.p_type == STP_PARAMETER_TYPE_STRING_LIST
    && d->resolutions.is_active && d->resolutions.bounds.str
    && (count = stp_string_list_count(d->resolutions.bounds.str)) > 0;
  if (!d->has_resolutions)
    count = 0;
  d->modes = calloc(count ? count : 1, sizeof *d->modes);
  for (size_t i = 0; i < count; i++)
    {
      mode_t_ *m = &d->modes[d->mode_count];
      m->name = stp_string_list_param(d->resolutions.bounds.str, i)->name;
      stp_vars_t *v = stp_vars_create_copy(d->defaults);
      stp_set_string_parameter(v, "Resolution", m->name);
      stp_describe_resolution(v, &m->x_dpi, &m->y_dpi);
      printing_modes(v, &m->color, &m->mono);
      stp_vars_destroy(v);
      if (m->x_dpi > 0 && m->y_dpi > 0)
        d->mode_count++;
    }
  if (d->mode_count == 0)
    {
      /* One mode: the driver's own choice. */
      d->has_resolutions = 0;
      mode_t_ *m = &d->modes[0];
      m->name = NULL;
      stp_describe_resolution(d->defaults, &m->x_dpi, &m->y_dpi);
      printing_modes(d->defaults, &m->color, &m->mono);
      d->mode_count = 1;
    }
  stp_describe_resolution(d->defaults, &d->default_x_dpi, &d->default_y_dpi);
  stp_parameter_t desc;
  stp_describe_parameter(d->defaults, "PrintingMode", &desc);
  d->default_color = !(desc.deflt.str && strcmp(desc.deflt.str, "BW") == 0);
  stp_parameter_description_destroy(&desc);
}

static int
load_driver(driver_t *d, const char *name)
{
  memset(d, 0, sizeof *d);
  d->printer = stp_get_printer_by_driver(name);
  if (!d->printer)
    return -1;
  d->defaults = stp_vars_create();
  stp_set_driver(d->defaults, name);
  stp_set_printer_defaults(d->defaults, d->printer);
  load_papers(d);
  load_modes(d);
  return 0;
}

static void
free_driver(driver_t *d)
{
  for (size_t i = 0; i < d->paper_count; i++)
    free(d->papers[i].paper);
  free(d->papers);
  free(d->modes);
  stp_parameter_description_destroy(&d->resolutions);
  stp_vars_destroy(d->defaults);
}

static void
format_resolution(char *out, size_t size, int x, int y)
{
  if (x == y)
    snprintf(out, size, "%ddpi", x);
  else
    snprintf(out, size, "%dx%ddpi", x, y);
}

/* ---- describe ------------------------------------------------------------ */

static int
describe(const driver_t *d)
{
  printf("driver=%s\n", stp_printer_get_driver(d->printer));
  printf("model=%s\n", stp_printer_get_long_name(d->printer));
  for (size_t i = 0; i < d->paper_count; i++)
    printf("media=%s\n", d->papers[i].pwg);
  if (d->default_paper)
    printf("media-default=%s\n", d->default_paper);

  char text[64];
  for (size_t i = 0; i < d->mode_count; i++)
    {
      if (d->modes[i].x_dpi <= 0 || d->modes[i].y_dpi <= 0)
        continue;   /* a driver that does not know its resolution */
      int seen = 0;
      for (size_t j = 0; j < i; j++)
        seen |= d->modes[j].x_dpi == d->modes[i].x_dpi && d->modes[j].y_dpi == d->modes[i].y_dpi;
      if (seen)
        continue;
      format_resolution(text, sizeof text, d->modes[i].x_dpi, d->modes[i].y_dpi);
      printf("resolution=%s\n", text);
    }
  if (d->default_x_dpi > 0 && d->default_y_dpi > 0)
    {
      format_resolution(text, sizeof text, d->default_x_dpi, d->default_y_dpi);
      printf("resolution-default=%s\n", text);
    }

  int color = 0, mono = 0;
  for (size_t i = 0; i < d->mode_count; i++)
    {
      color |= d->modes[i].color;
      mono |= d->modes[i].mono;
    }
  if (color)
    printf("color-mode=color\n");
  if (mono)
    printf("color-mode=monochrome\n");
  printf("color-mode-default=%s\n", d->default_color ? "color" : "monochrome");
  fflush(stdout);
  return ferror(stdout) ? EXIT_DRIVER_FAILED : 0;
}

/* ---- print: options ------------------------------------------------------ */

typedef struct
{
  const paper_t *paper;   /* NULL: from each page, else the default */
  const mode_t_ *mode;
  const char *printing_mode;  /* "Color", "BW" or NULL for the default */
} settings_t;

static int
parse_resolution(const char *value, int *x, int *y)
{
  char *end;
  long a = strtol(value, &end, 10);
  long b = a;
  if (end == value || a <= 0 || a > 100000)
    return -1;
  if (*end == 'x')
    {
      const char *start = end + 1;
      b = strtol(start, &end, 10);
      if (end == start || b <= 0 || b > 100000)
        return -1;
    }
  if (*end != '\0' && strcmp(end, "dpi") != 0)
    return -1;
  *x = (int)a;
  *y = (int)b;
  return 0;
}

static int
mode_fits(const mode_t_ *m, int x, int y, const char *printing_mode)
{
  if (x && (m->x_dpi != x || m->y_dpi != y))
    return 0;
  if (printing_mode && strcmp(printing_mode, "BW") == 0 && !m->mono)
    return 0;
  if (printing_mode && strcmp(printing_mode, "Color") == 0 && !m->color)
    return 0;
  return 1;
}

/* The driver's default mode if it fits, else the first one that does. */
static const mode_t_ *
choose_mode(const driver_t *d, int x, int y, const char *printing_mode)
{
  const char *deflt = d->has_resolutions ? d->resolutions.deflt.str : NULL;
  for (size_t i = 0; i < d->mode_count; i++)
    if (deflt && d->modes[i].name && strcmp(d->modes[i].name, deflt) == 0
        && mode_fits(&d->modes[i], x, y, printing_mode))
      return &d->modes[i];
  for (size_t i = 0; i < d->mode_count; i++)
    if (mode_fits(&d->modes[i], x, y, printing_mode))
      return &d->modes[i];
  return NULL;
}

static int
parse_options(const driver_t *d, char **options, int count, settings_t *s)
{
  int x = 0, y = 0;
  memset(s, 0, sizeof *s);
  for (int i = 0; i < count; i++)
    {
      const char *option = options[i];
      const char *eq = strchr(option, '=');
      if (!eq)
        return usage_error("an option is not KEY=VALUE: ", option);
      const char *value = eq + 1;
      size_t key_length = (size_t)(eq - option);
      if (key_length == 5 && strncmp(option, "media", 5) == 0)
        {
          s->paper = paper_by_pwg(d, value);
          if (!s->paper)
            return usage_error("the driver has no paper ", value);
        }
      else if (key_length == 10 && strncmp(option, "resolution", 10) == 0)
        {
          if (parse_resolution(value, &x, &y) != 0)
            return usage_error("a resolution is Ndpi or XxYdpi, not ", value);
        }
      else if (key_length == 10 && strncmp(option, "color-mode", 10) == 0)
        {
          if (strcmp(value, "color") == 0)
            s->printing_mode = "Color";
          else if (strcmp(value, "monochrome") == 0)
            s->printing_mode = "BW";
          else
            return usage_error("color-mode is color or monochrome, not ", value);
        }
      else
        return usage_error("unknown option ", option);
    }
  s->mode = choose_mode(d, x, y, s->printing_mode);
  if (!s->mode)
    return usage_error("the driver offers no such resolution and colour mode", NULL);
  return 0;
}

/* ---- print: the job ------------------------------------------------------ */

typedef struct
{
  pwg_reader_t *reader;
  pwg_page_t page;
  unsigned char *line;      /* one raster line */
  unsigned next_line;       /* the next raster line to read */
  int x0, y0;               /* raster pixel at the printable area's corner */
  int width, height;        /* the printable area in raster pixels */
  int raster_failed;
  int write_failed;
} job_t;

static void
write_stdout(void *data, const char *buffer, size_t bytes)
{
  job_t *job = data;
  if (job->write_failed)
    return;
  if (fwrite(buffer, 1, bytes, stdout) != bytes)
    {
      job->write_failed = 1;
      fprintf(stderr, "print-engine: writing the printer's bytes failed\n");
    }
}

static int
image_width(stp_image_t *image)
{
  return ((job_t *)image->rep)->width;
}

static int
image_height(stp_image_t *image)
{
  return ((job_t *)image->rep)->height;
}

static const char *
image_appname(stp_image_t *image)
{
  (void)image;
  return "print-engine";
}

/* Row row of the printable area: raster pixels outside the raster are white. */
static stp_image_status_t
image_get_row(stp_image_t *image, unsigned char *data, size_t byte_limit, int row)
{
  job_t *job = image->rep;
  unsigned channels = job->page.channels;
  if (job->raster_failed || job->write_failed)
    return STP_IMAGE_STATUS_ABORT;
  memset(data, 0xff, byte_limit);
  long target = (long)job->y0 + row;
  if (target < 0 || target >= (long)job->page.height)
    return STP_IMAGE_STATUS_OK;
  while (job->next_line <= (unsigned long)target)
    {
      if (pwg_read_line(job->reader, job->line) != 0)
        {
          job->raster_failed = 1;
          fprintf(stderr, "print-engine: bad raster: %s\n", pwg_reader_error(job->reader));
          return STP_IMAGE_STATUS_ABORT;
        }
      job->next_line++;
    }
  long from = job->x0 < 0 ? 0 : job->x0;
  long to = (long)job->x0 + job->width;
  if (to > (long)job->page.width)
    to = job->page.width;
  if (to > from)
    {
      size_t offset = (size_t)(from - job->x0) * channels;
      size_t bytes = (size_t)(to - from) * channels;
      if (offset + bytes > byte_limit)
        bytes = offset < byte_limit ? byte_limit - offset : 0;
      memcpy(data + offset, job->line + (size_t)from * channels, bytes);
    }
  return STP_IMAGE_STATUS_OK;
}

/* The paper for a page: the media option, else the page's own media name
   or size, else the driver's default. */
static const paper_t *
page_paper(const driver_t *d, const settings_t *s, const pwg_page_t *page)
{
  if (s->paper)
    return s->paper;
  if (page->media_name[0] && paper_by_pwg(d, page->media_name))
    return paper_by_pwg(d, page->media_name);
  for (size_t i = 0; i < d->paper_count; i++)
    {
      const stp_papersize_t *size = stp_describe_papersize(d->defaults, d->papers[i].paper);
      if (size && fabs(size->width - page->page_width) <= 1
          && fabs(size->height - page->page_height) <= 1)
        return &d->papers[i];
    }
  return d->default_paper ? paper_by_pwg(d, d->default_paper) : NULL;
}

/* Clears string settings the driver no longer offers after the others
   changed, and sets the mandatory ones back to their defaults. */
static void
validate(stp_vars_t *v)
{
  stp_parameter_list_t params = stp_get_parameter_list(v);
  size_t count = stp_parameter_list_count(params);
  for (size_t i = 0; i < count; i++)
    {
      const stp_parameter_t *param = stp_parameter_list_param(params, i);
      stp_parameter_t desc;
      stp_describe_parameter(v, param->name, &desc);
      if (desc.p_type == STP_PARAMETER_TYPE_STRING_LIST
          && !string_list_has(desc.bounds.str, stp_get_string_parameter(v, desc.name)))
        {
          stp_clear_string_parameter(v, desc.name);
          if (!desc.read_only && desc.is_mandatory && desc.is_active && desc.deflt.str)
            stp_set_string_parameter(v, desc.name, desc.deflt.str);
        }
      stp_parameter_description_destroy(&desc);
    }
  stp_parameter_list_destroy(params);
}

/* The settings for one page, with the printable area placed on the raster. */
static stp_vars_t *
page_vars(const driver_t *d, const settings_t *s, job_t *job, int number)
{
  const pwg_page_t *page = &job->page;
  stp_vars_t *v = stp_vars_create_copy(d->defaults);
  stp_set_outfunc(v, write_stdout);
  stp_set_outdata(v, job);
  stp_set_errfunc(v, write_stderr);
  stp_set_errdata(v, NULL);
  stp_set_string_parameter(v, "JobMode", "Job");
  stp_set_string_parameter(v, "ChannelBitDepth", "8");
  stp_set_string_parameter(v, "InputImageType", page->channels == 1 ? "Whitescale" : "RGB");
  stp_set_float_parameter(v, "AppGamma", 1.0);
  if (s->mode->name)
    stp_set_string_parameter(v, "Resolution", s->mode->name);
  if (s->printing_mode)
    stp_set_string_parameter(v, "PrintingMode", s->printing_mode);

  const paper_t *paper = page_paper(d, s, page);
  if (paper)
    {
      stp_set_string_parameter(v, "PageSize", paper->paper);
      const stp_papersize_t *size = stp_describe_papersize(v, paper->paper);
      stp_set_page_width(v, size->width);
      stp_set_page_height(v, size->height);
    }
  validate(v);
  stp_merge_printvars(v, stp_printer_get_defaults(d->printer));
  stp_set_int_parameter(v, "PageNumber", number);

  stp_dimension_t left, right, bottom, top;
  stp_get_imageable_area(v, &left, &right, &bottom, &top);
  stp_set_left(v, left);
  stp_set_top(v, top);
  stp_set_width(v, right - left);
  stp_set_height(v, bottom - top);

  job->x0 = (int)lround(left * page->x_dpi / 72.0);
  job->y0 = (int)lround(top * page->y_dpi / 72.0);
  job->width = (int)lround((right - left) * page->x_dpi / 72.0);
  job->height = (int)lround((bottom - top) * page->y_dpi / 72.0);
  job->next_line = 0;
  return v;
}

static int
print_job(const driver_t *d, const settings_t *s)
{
  job_t job;
  memset(&job, 0, sizeof job);
  job.reader = pwg_reader_open(stdin);
  if (!job.reader)
    return EXIT_DRIVER_FAILED;
  stp_image_t image = {
    .width = image_width,
    .height = image_height,
    .get_row = image_get_row,
    .get_appname = image_appname,
    .rep = &job,
  };

  int status = 0;
  int got = pwg_next_page(job.reader, &job.page);
  if (got <= 0)
    {
      fprintf(stderr, "print-engine: bad raster: %s\n",
              got == 0 ? "the input has no page" : pwg_reader_error(job.reader));
      pwg_reader_close(job.reader);
      return EXIT_BAD_RASTER;
    }

  stp_vars_t *v = NULL;
  int started = 0;
  for (int number = 0; got > 0; number++)
    {
      if (v)
        stp_vars_destroy(v);
      unsigned char *line = realloc(job.line, (size_t)job.page.width * job.page.channels);
      if (!line)
        {
          status = EXIT_DRIVER_FAILED;
          break;
        }
      job.line = line;
      v = page_vars(d, s, &job, number);
      if (job.width <= 0 || job.height <= 0 || !stp_verify(v))
        {
          fprintf(stderr, "print-engine: the driver refused the settings of page %d\n", number + 1);
          status = EXIT_DRIVER_FAILED;
          break;
        }
      if (!started)
        {
          stp_start_job(v, &image);
          started = 1;
        }
      int printed = stp_print(v, &image);
      if (job.raster_failed)
        status = EXIT_BAD_RASTER;
      else if (job.write_failed)
        status = EXIT_DRIVER_FAILED;
      else if (!printed)
        {
          fprintf(stderr, "print-engine: the driver failed on page %d\n", number + 1);
          status = EXIT_DRIVER_FAILED;
        }
      if (status)
        break;
      got = pwg_next_page(job.reader, &job.page);
      if (got < 0)
        {
          fprintf(stderr, "print-engine: bad raster: %s\n", pwg_reader_error(job.reader));
          status = EXIT_BAD_RASTER;
        }
    }
  /* A job once started is always ended, so the printer is not left
     waiting in the middle of it. */
  if (started)
    stp_end_job(v, &image);
  if (v)
    stp_vars_destroy(v);
  if (fflush(stdout) != 0 || ferror(stdout))
    {
      if (!job.write_failed)
        fprintf(stderr, "print-engine: writing the printer's bytes failed\n");
      if (!status)
        status = EXIT_DRIVER_FAILED;
    }
  free(job.line);
  pwg_reader_close(job.reader);
  return status;
}

/* ---- main ---------------------------------------------------------------- */

int
main(int argc, char **argv)
{
  /* A closed stdout fails the write, and the job, with exit code 4. */
  signal(SIGPIPE, SIG_IGN);

  if (argc < 2)
    return usage_error(NULL, NULL);
  const char *command = argv[1];
  if (strcmp(command, "--help") == 0 || strcmp(command, "-h") == 0)
    {
      fputs(usage_text, stdout);
      return 0;
    }
  int is_print = strcmp(command, "print") == 0;
  if (!is_print && strcmp(command, "describe") != 0)
    return usage_error("unknown command ", command);

  const char *driver_name = NULL;
  char **options = calloc((size_t)argc, sizeof *options);
  int option_count = 0;
  for (int i = 2; i < argc; i++)
    {
      if (strcmp(argv[i], "--driver") == 0 && i + 1 < argc)
        driver_name = argv[++i];
      else if (is_print && strcmp(argv[i], "--option") == 0 && i + 1 < argc)
        options[option_count++] = argv[++i];
      else
        {
          free(options);
          return usage_error("unknown argument ", argv[i]);
        }
    }
  if (!driver_name)
    {
      free(options);
      return usage_error("--driver NAME is missing", NULL);
    }
  const char *data = getenv("STP_DATA_PATH");
  if (!data || !*data)
    {
      free(options);
      return usage_error("STP_DATA_PATH does not name Gutenprint's data directory", NULL);
    }

  stp_set_global_errfunc(write_stderr);
  stp_set_global_dbgfunc(write_stderr);
  stp_init();
  driver_t driver;
  if (load_driver(&driver, driver_name) != 0)
    {
      free(options);
      fprintf(stderr, "print-engine: unknown driver %s (or no printer data in %s)\n",
              driver_name, data);
      return EXIT_USAGE;
    }

  int status;
  if (is_print)
    {
      settings_t settings;
      status = parse_options(&driver, options, option_count, &settings);
      if (status == 0)
        status = print_job(&driver, &settings);
    }
  else
    status = describe(&driver);
  free(options);
  free_driver(&driver);
  return status;
}
