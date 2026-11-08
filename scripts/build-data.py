#!/usr/bin/env python3
# print-engine-android: builds Gutenprint's data directory.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: build-data.py XML_SOURCE_DIR OUTPUT_DIR
#
# XML_SOURCE_DIR is Gutenprint's src/xml. OUTPUT_DIR gets the files that
# upstream's `make install` puts in share/gutenprint/5.3/xml: every file a
# Makefile.am under src/xml lists in pkgxmldata_DATA, at the same relative
# path, for every printer family. Upstream's build copies these files
# unchanged; it builds nothing else that the library reads. OUTPUT_DIR is
# replaced, so a file dropped upstream does not linger.
#
# The script fails if a Makefile.am installs into a directory other than its
# own, or if an .xml file under src/xml is installed by no Makefile.am, so a
# change in upstream's layout fails the build instead of shipping less data.
import os
import re
import shutil
import sys

ASSIGNMENT = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=(.*)$")
XML_DATA_DIR = "$(pkgdatadir)/@GUTENPRINT_MAJOR_VERSION@.@GUTENPRINT_MINOR_VERSION@/xml"


def variables(makefile_am):
    """The plain NAME = value assignments of a Makefile.am, continuations joined."""
    with open(makefile_am, encoding="utf-8") as f:
        text = f.read().replace("\\\n", " ")
    found = {}
    for line in text.splitlines():
        match = ASSIGNMENT.match(line)
        if match:
            found[match.group(1)] = match.group(2).split()
    return found


def installed_files(source, relative=""):
    """(relative path) for every file the Makefile.am tree under source installs."""
    directory = os.path.join(source, relative)
    found = variables(os.path.join(directory, "Makefile.am"))
    files = found.get("pkgxmldata_DATA", [])
    if files:
        want = XML_DATA_DIR + ("/" + relative if relative else "")
        got = " ".join(found.get("pkgxmldatadir", []))
        if got != want:
            sys.exit(f"{directory}/Makefile.am installs into {got}, expected {want}")
    for name in files:
        yield os.path.join(relative, name)
    for subdir in found.get("SUBDIRS", []):
        yield from installed_files(source, os.path.join(relative, subdir))


def main():
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} XML_SOURCE_DIR OUTPUT_DIR")
    source, output = sys.argv[1], sys.argv[2]
    files = sorted(set(installed_files(source)))

    every_xml = set()
    for root, _, names in os.walk(source):
        for name in names:
            if name.endswith(".xml"):
                every_xml.add(os.path.relpath(os.path.join(root, name), source))
    missed = sorted(every_xml - set(files))
    if missed:
        sys.exit("XML files that no Makefile.am installs: " + ", ".join(missed))

    staging = output + ".tmp"
    shutil.rmtree(staging, ignore_errors=True)
    for relative in files:
        target = os.path.join(staging, relative)
        os.makedirs(os.path.dirname(target), exist_ok=True)
        shutil.copyfile(os.path.join(source, relative), target)
    shutil.rmtree(output, ignore_errors=True)
    os.rename(staging, output)
    print(f"{output}: {len(files)} files")


if __name__ == "__main__":
    main()
