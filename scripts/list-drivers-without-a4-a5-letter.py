#!/usr/bin/env python3
# print-engine-android: writes the list of the drivers whose papers include
# none of A4, A5 and Letter, which the printer table leaves out.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: list-drivers-without-a4-a5-letter.py PROGRAM DATA_DIR > LIST
#
# PROGRAM is the host build of print-engine, DATA_DIR the data directory it
# reads (scripts/build-data.py makes it). The script runs `PROGRAM describe`
# on every driver that the data's printers/*.xml lists, read as XML, and
# writes on stdout, in name order, each driver whose media lines name none of
# iso_a4_210x297mm, iso_a5_148x210mm and na_letter_8.5x11in, after a comment
# header. scripts/generate-resources.py takes this list as its LEAVE_OUT. The
# repository keeps it as scripts/drivers-without-a4-a5-letter.txt, because
# the Android module's build has no host program to run; a host test fails
# when that file is not what this script writes.
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
from concurrent.futures import ThreadPoolExecutor

PAPERS = ("iso_a4_210x297mm", "iso_a5_148x210mm", "na_letter_8.5x11in")
HEADER = """\
# print-engine-android: the drivers whose papers include none of A4, A5 and
# Letter (iso_a4_210x297mm, iso_a5_148x210mm, na_letter_8.5x11in), one per
# line. scripts/generate-resources.py leaves them out of the printer table.
# Generated; do not edit. Remake it after a change to Gutenprint or its data:
#   scripts/list-drivers-without-a4-a5-letter.py build/print-engine build/data \\
#     > scripts/drivers-without-a4-a5-letter.txt
"""


def drivers(data_dir):
    """The driver names of the data's printers/*.xml."""
    directory = os.path.join(data_dir, "printers")
    names = set()
    for name in os.listdir(directory):
        if name.endswith(".xml"):
            for element in ET.parse(os.path.join(directory, name)).getroot().iter():
                if element.tag.rpartition("}")[2] == "printer" and element.get("driver"):
                    names.add(element.get("driver"))
    if not names:
        raise SystemExit(f"list-drivers-without-a4-a5-letter.py: no printers in {data_dir}")
    return sorted(names)


def has_a_paper(program, data_dir, driver):
    """Whether describe lists one of PAPERS for driver; fails the script when
    describe fails."""
    result = subprocess.run([program, "describe", "--driver", driver],
                            env={"STP_DATA_PATH": data_dir}, capture_output=True,
                            timeout=60, check=False)
    if result.returncode != 0:
        raise SystemExit(f"list-drivers-without-a4-a5-letter.py: describe --driver {driver}"
                         f" exited {result.returncode}: {result.stderr.decode().strip()}")
    return any(f"media={paper}" in result.stdout.decode().splitlines() for paper in PAPERS)


def main(argv):
    if len(argv) != 3:
        sys.stderr.write("usage: list-drivers-without-a4-a5-letter.py PROGRAM DATA_DIR\n")
        return 2
    program, data_dir = argv[1], argv[2]
    names = drivers(data_dir)
    with ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as pool:
        found = list(pool.map(lambda driver: has_a_paper(program, data_dir, driver), names))
    sys.stdout.write(HEADER + "".join(f"{driver}\n" for driver, has in zip(names, found)
                                      if not has))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
