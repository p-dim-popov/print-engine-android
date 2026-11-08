/* print-engine-android
   Copyright (C) 2026 Petar Popov

   PWG media names (PWG 5101.1) for Gutenprint's papers.

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

#ifndef PWG_MEDIA_H
#define PWG_MEDIA_H

#include <stddef.h>

/* The size a self-describing PWG media name states, in points, and
   whether it is given in millimetres: 0, or -1 when the name states none. */
int pwg_media_size(const char *name, double *width, double *height, int *metric);

/* The PWG media name of a paper of width x height points: the standard
   name of that size (within a point, the paper's own unit preferred), or
   else "om_<name>_<w>x<h>mm" for a metric paper and "oe_<name>_<w>x<h>in"
   for another, from the paper's Gutenprint name. */
void pwg_media_name(const char *paper, double width, double height, int metric,
                    char *out, size_t size);

#endif
