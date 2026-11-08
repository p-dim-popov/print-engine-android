# print-engine-android: libgutenprint 5.3.5 as a static library.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# The sources of src/main/Makefile.am's libgutenprint_la_SOURCES with every
# family and colour module linked in (configure --with-modules=static), and
# no CUPS, GIMP or NLS. config.h is written by hand (src/gutenprint-config);
# gutenprint-version.h is made from its .in file, as configure does.

set(GUTENPRINT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gutenprint)

set(GUTENPRINT_MAJOR_VERSION 5)
set(GUTENPRINT_MINOR_VERSION 3)
set(GUTENPRINT_MICRO_VERSION 5)
set(GUTENPRINT_CURRENT_INTERFACE 15)
set(GUTENPRINT_BINARY_AGE 6)
set(GUTENPRINT_INTERFACE_AGE 0)
configure_file(${GUTENPRINT_DIR}/include/gutenprint/gutenprint-version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/gutenprint-include/gutenprint/gutenprint-version.h @ONLY)

set(GUTENPRINT_MAIN ${GUTENPRINT_DIR}/src/main)
set(GUTENPRINT_SOURCES
  # libgutenprint_la_SOURCES
  array.c bit-ops.c channel.c color.c curve.c curve-cache.c
  dither-ed.c dither-eventone.c dither-inks.c dither-main.c dither-ordered.c
  dither-very-fast.c dither-predithered.c generic-options.c image.c
  buffer-image.c module.c path.c print-dither-matrices.c print-list.c
  print-papers.c print-util.c print-vars.c print-version.c print-weave.c
  printers.c refcache.c sequence.c string-list.c xml.c
  # mxml_SOURCES
  mxml-attr.c mxml-file.c mxml-node.c mxml-search.c
  # module_SOURCES: the colour module and every family driver
  print-color.c color-conversions.c
  print-canon.c
  print-escp2.c escp2-driver.c print-escp2-data.c escp2-channels.c
  escp2-papers.c escp2-resolutions.c
  print-lexmark.c print-pcl.c print-dpl.c
  print-ps.c xmlppd.c
  print-dyesub.c print-raw.c)
list(TRANSFORM GUTENPRINT_SOURCES PREPEND ${GUTENPRINT_MAIN}/)

add_library(gutenprint STATIC ${GUTENPRINT_SOURCES})
target_include_directories(gutenprint
  PUBLIC ${GUTENPRINT_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/gutenprint-include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/gutenprint-config ${GUTENPRINT_MAIN})
# Upstream builds these files as C99 with POSIX 2008. The compiled-in data,
# module and locale paths are empty: the program requires STP_DATA_PATH.
set_target_properties(gutenprint PROPERTIES C_STANDARD 99 C_EXTENSIONS OFF)
target_compile_definitions(gutenprint PRIVATE
  HAVE_CONFIG_H
  _POSIX_C_SOURCE=200809L
  PACKAGE_LOCALE_DIR=""
  PACKAGE_DATA_DIR=""
  PACKAGE_LIB_DIR=""
  PACKAGE_BIN_DIR=""
  PKGMODULEDIR=""
  PKGXMLDATADIR="")
# Upstream's warning set is on; the code is upstream's, so findings there do
# not fail the build.
target_compile_options(gutenprint PRIVATE -Wno-unused-parameter -Wno-sign-compare
  -Wno-deprecated-declarations -Wno-missing-field-initializers)
target_link_libraries(gutenprint PUBLIC m)
