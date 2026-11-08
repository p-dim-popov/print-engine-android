/* print-engine-android
   Copyright (C) 2026 Petar Popov

   config.h for Gutenprint 5.3.5, written by hand for glibc and bionic.
   Upstream generates it with configure; these are the values that
   configure finds on Linux with --without-cups --with-modules=static
   --disable-nls, less the ones only the CUPS, GIMP and test programs use.

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

#ifndef PRINT_ENGINE_GUTENPRINT_CONFIG_H
#define PRINT_ENGINE_GUTENPRINT_CONFIG_H

#define PACKAGE "gutenprint"
#define PACKAGE_NAME "gutenprint"
#define PACKAGE_STRING "gutenprint 5.3.5"
#define PACKAGE_TARNAME "gutenprint"
#define PACKAGE_URL "https://gimp-print.sourceforge.net"
#define PACKAGE_BUGREPORT "gimp-print-devel@lists.sourceforge.net"
#define PACKAGE_VERSION "5.3.5"
#define VERSION "5.3.5"
#define GUTENPRINT_BASE_VERSION "5.3.5"
#define GUTENPRINT_RELEASE_VERSION "5.3"
#define RELEASE_DATE "12 Mar 2025"

/* Modules are linked in (no MODULE, USE_LTDL or USE_DLOPEN), and there is
   no message catalogue (no ENABLE_NLS). */
#define ENABLE_SHARED "no"
#define ENABLE_STATIC "yes"

#define HAVE_GCC_ATTRIBUTES 1
#if !defined(HAVE_GCC_ATTRIBUTES) && !defined(__attribute__)
#define __attribute__(attr)
#endif

#define HAVE_DECL_STRDUP 1
#define HAVE_DECL_STRNDUP 1
#define HAVE_DLFCN_H 1
#define HAVE_FCNTL_H 1
#define HAVE_GETOPT_H 1
#define HAVE_GETOPT_LONG 1
#define HAVE_GETUID 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIBREADLINE 0
#define HAVE_LIMITS_H 1
#define HAVE_LOCALE_H 1
#define HAVE_NANOSLEEP 1
#define HAVE_POLL 1
#define HAVE_SETENV 1
#define HAVE_STDARG_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_TIME_H 1
#define HAVE_UNISTD_H 1
#define HAVE_USLEEP 1
#define HAVE_WAITPID 1
#define STDC_HEADERS 1

#endif
