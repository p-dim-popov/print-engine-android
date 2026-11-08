# print-engine-android: the print-engine program over Gutenprint.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Targets:
#   gutenprint     libgutenprint 5.3.5, static, every family linked in
#   print-engine   the program: describe and print (src/print-engine.c);
#                  on Android the file is libprintengine.so
#   data           Gutenprint's XML data for every family, in build/data
#                  (scripts/build-data.py), the directory STP_DATA_PATH names
#   check-duplicate-printers  host only: upstream's check of the printer data
cmake_minimum_required(VERSION 3.22)
project(print_engine C)

# Every Android build is linked for 16 KB pages: the NDK's toolchain option
# sets the linker's page size and hides bionic's PAGE_SIZE constant. The
# module's Gradle build and scripts/build-android.sh both pass it; a build
# without it fails here.
if(ANDROID AND NOT ANDROID_SUPPORT_FLEXIBLE_PAGE_SIZES)
  message(FATAL_ERROR "Configure Android builds with -DANDROID_SUPPORT_FLEXIBLE_PAGE_SIZES=ON")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/Gutenprint.cmake)

add_executable(print-engine
  src/print-engine.c
  src/pwg-raster.c
  src/pwg-media.c)
target_compile_definitions(print-engine PRIVATE _POSIX_C_SOURCE=200809L)
target_compile_options(print-engine PRIVATE -Wall -Wextra -Werror)
target_link_libraries(print-engine PRIVATE gutenprint)
if(ANDROID)
  # Android extracts only files named lib<name>.so from an APK's native
  # libraries; the program is one of them.
  set_target_properties(print-engine PROPERTIES OUTPUT_NAME libprintengine.so SUFFIX "")
endif()

if(NOT ANDROID)
  find_package(Python3 REQUIRED COMPONENTS Interpreter)

  # Gutenprint's data is the same on every architecture, so the host builds
  # it; an Android build packs the host's copy.
  set(PRINT_ENGINE_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
  add_custom_target(data ALL
    COMMAND Python3::Interpreter -I ${CMAKE_CURRENT_SOURCE_DIR}/scripts/build-data.py
      ${GUTENPRINT_DIR}/src/xml ${PRINT_ENGINE_DATA_DIR}
    COMMENT "Building Gutenprint's data in ${PRINT_ENGINE_DATA_DIR}"
    VERBATIM)

  # Upstream runs this check on its printer data when it builds the data.
  add_executable(check-duplicate-printers
    ${GUTENPRINT_DIR}/src/xml/printers/check_duplicate_printers.test.c)
  target_include_directories(check-duplicate-printers PRIVATE src/gutenprint-config)
  target_compile_definitions(check-duplicate-printers PRIVATE HAVE_CONFIG_H _POSIX_C_SOURCE=200809L)
  target_link_libraries(check-duplicate-printers PRIVATE gutenprint)

  enable_testing()
  add_test(NAME check-duplicate-printers COMMAND check-duplicate-printers)
  set_tests_properties(check-duplicate-printers PROPERTIES
    ENVIRONMENT STP_DATA_PATH=${PRINT_ENGINE_DATA_DIR} TIMEOUT 60)
  add_test(NAME print-engine
    COMMAND Python3::Interpreter -I -m unittest discover -s ${CMAKE_CURRENT_SOURCE_DIR}/tests -p "*_test.py" -v)
  set_tests_properties(print-engine PROPERTIES
    ENVIRONMENT "PRINT_ENGINE=$<TARGET_FILE:print-engine>;STP_DATA_PATH=${PRINT_ENGINE_DATA_DIR}"
    TIMEOUT 300)
endif()
