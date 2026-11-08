# print-engine-android: host tests of the printer table generator.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Each test runs scripts/generate-resources.py on a data directory, as a build
# does, and reads the table it writes as a consumer does: one row per
# <printer mfg mdl driver/>, looked up by an IEEE 1284 device ID's MFG and
# MDL with case, spaces and a trailing "series" set aside. CTest sets
# STP_DATA_PATH (Gutenprint's data directory, as the build makes it).
import os
import re
import subprocess
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
GENERATOR = os.path.join(HERE, "..", "scripts", "generate-resources.py")
DATA = os.environ.get("STP_DATA_PATH", "build/data")
PROGRAM = os.environ.get("PRINT_ENGINE", "build/print-engine")

# The MP250's device ID, as measured on its USB printer interface.
MP250_DEVICE_ID = ("MFG:Canon;CMD:BJL,BJRaster3,BSCCe,IVEC,IVECPLI;SOJ:TXT01;"
                   "MDL:MP250 series;CLS:PRINTER;VER:1.020")


def fields(device_id):
    pairs = (field.split(":", 1) for field in device_id.split(";") if ":" in field)
    return {name.strip().upper(): value for name, value in pairs}


def normalised(text):
    text = " ".join(word for word in re.split("[ \t]", text.lower()) if word)
    return text.removesuffix(" series")


def key(make, model):
    return f"{normalised(make)}|{normalised(model)}"


def resources(data_dir):
    """Runs the generator on data_dir; returns the resources it wrote: the
    table's rows, in order, as (mfg, mdl, driver), and the string resources."""
    with tempfile.TemporaryDirectory() as out:
        result = subprocess.run([sys.executable, "-I", GENERATOR, data_dir, out],
                                capture_output=True, timeout=120, check=False)
        assert result.returncode == 0, result.stderr.decode()
        assert sorted(os.listdir(out)) == ["values", "xml"], os.listdir(out)
        table = ET.parse(os.path.join(out, "xml", "print_engine_printers.xml")).getroot()
        values = ET.parse(os.path.join(out, "values", "print_engine.xml")).getroot()
    rows = [(row.get("mfg"), row.get("mdl"), row.get("driver")) for row in table.iter("printer")]
    strings = {string.get("name"): string.text for string in values.iter("string")}
    return rows, strings


def generate(data_dir):
    return resources(data_dir)[0]


def data_version(data_dir):
    return resources(data_dir)[1]["print_engine_data_version"]


def lookup(rows, device_id):
    """The driver a consumer finds for device_id: the first row for its key."""
    id_fields = fields(device_id)
    wanted = key(id_fields.get("MFG", id_fields.get("MANUFACTURER", "")),
                 id_fields.get("MDL", id_fields.get("MODEL", "")))
    for mfg, mdl, driver in rows:
        if key(mfg, mdl) == wanted:
            return driver
    return None


class GutenprintData(unittest.TestCase):
    """The table generated from the data directory the build makes."""

    @classmethod
    def setUpClass(cls):
        cls.rows = generate(DATA)

    def test_the_mp250s_device_id_maps_to_its_driver(self):
        self.assertEqual(lookup(self.rows, MP250_DEVICE_ID), "bjc-MP250-series")

    def test_every_driver_in_the_table_is_one_the_program_knows(self):
        drivers = sorted({driver for _, _, driver in self.rows})

        def describes(driver):
            result = subprocess.run([PROGRAM, "describe", "--driver", driver],
                                    env={"STP_DATA_PATH": DATA}, capture_output=True,
                                    timeout=60, check=False)
            return driver, result.returncode

        with ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as pool:
            unknown = [driver for driver, code in pool.map(describes, drivers) if code != 0]
        self.assertEqual(unknown, [])
        self.assertGreater(len(drivers), 3000)

    def test_a_printer_inside_an_xml_comment_gives_no_row(self):
        # canon.xml lists the iP100 family inside a comment; Gutenprint does not load it.
        self.assertNotIn("bjc-iP100-series", {driver for _, _, driver in self.rows})

    def test_raw_and_postscript_drivers_give_no_row(self):
        drivers = {driver for _, _, driver in self.rows}
        for driver in ("raw-data-8", "raw-data-16", "ps", "ps2"):
            self.assertNotIn(driver, drivers)

    def test_each_model_has_one_row(self):
        keys = [key(mfg, mdl) for mfg, mdl, _ in self.rows]
        self.assertEqual(len(keys), len(set(keys)))


def data_with(**files):
    """A data directory whose printers/<name>.xml hold the given families."""
    directory = tempfile.mkdtemp()
    os.mkdir(os.path.join(directory, "printers"))
    for name, families in files.items():
        with open(os.path.join(directory, "printers", f"{name}.xml"), "w", encoding="utf-8") as f:
            f.write('<?xml version="1.0"?>\n'
                    '<gutenprint xmlns="http://gimp-print.sourceforge.net/xsd/gp.xsd-1.0">'
                    f"<printdef>{families}</printdef></gutenprint>\n")
    return directory


class Rows(unittest.TestCase):
    """The rules by which printer entries become rows."""

    def rows(self, **files):
        directory = data_with(**files)
        self.addCleanup(lambda: subprocess.run(["rm", "-rf", directory], check=True))
        return generate(directory)

    def test_a_printer_gives_a_row_from_its_device_id_and_one_from_its_name(self):
        rows = self.rows(canon='<family name="canon">'
                         '<printer name="Canon PIXMA MP250" manufacturer="Canon" driver="bjc-mp250"'
                         ' deviceid="MFG:Canon;CMD:BJL;MDL:MP250 series;CLS:PRINTER;" />'
                         "</family>")
        self.assertEqual(rows, [("Canon", "MP250 series", "bjc-mp250"),
                                ("Canon", "PIXMA MP250", "bjc-mp250")])

    def test_long_device_id_keys_count_as_mfg_and_mdl(self):
        rows = self.rows(dyesub='<family name="dyesub">'
                         '<printer name="Citizen CX" manufacturer="Citizen" driver="citizen-cx"'
                         ' deviceid="MANUFACTURER:CITIZEN SYSTEMS ;MODEL:CX;" />'
                         "</family>")
        self.assertEqual(lookup(rows, "MFG:Citizen Systems;MDL:CX;"), "citizen-cx")

    def test_a_device_id_without_a_model_gives_only_the_name_row(self):
        rows = self.rows(dyesub='<family name="dyesub">'
                         '<printer name="Kodak 605" manufacturer="Kodak" driver="kodak-605"'
                         ' deviceid="MFG:Eastman Kodak Company;MCL:KODAK 605;" />'
                         "</family>")
        self.assertEqual(rows, [("Kodak", "605", "kodak-605")])

    def test_a_name_that_does_not_start_with_the_manufacturer_gives_no_row(self):
        rows = self.rows(dpl='<family name="dpl">'
                         '<printer name="Datamax-ONeil H4212" manufacturer="DatamaxONeil" driver="dmx" />'
                         "</family>")
        self.assertEqual(rows, [])

    def test_device_id_rows_win_over_name_rows_and_the_first_row_of_a_model_wins(self):
        rows = self.rows(canon='<family name="canon">'
                         '<printer name="Canon MP280 series" manufacturer="Canon" driver="by-name" />'
                         '<printer name="Canon PIXMA MP280" manufacturer="Canon" driver="by-id"'
                         ' deviceid="MFG:Canon;MDL:MP280 series;" />'
                         '<printer name="Canon PIXMA MP280 X" manufacturer="Canon" driver="second-id"'
                         ' deviceid="MFG:CANON;MDL:  mp280\tSERIES ;" />'
                         "</family>")
        self.assertEqual(lookup(rows, "MFG:Canon;MDL:MP280 series;"), "by-id")
        self.assertEqual(lookup(rows, "MFG:canon;MDL:MP280;"), "by-id")
        self.assertEqual([driver for mfg, mdl, driver in rows if key(mfg, mdl) == "canon|mp280"],
                         ["by-id"])

    def test_a_trailing_series_is_set_aside_only_as_a_word(self):
        rows = self.rows(pcl='<family name="pcl">'
                         '<printer name="HP Officejet Series 300" manufacturer="HP" driver="oj-300" />'
                         '<printer name="HP Thinseries" manufacturer="HP" driver="thin" />'
                         "</family>")
        self.assertEqual(lookup(rows, "MFG:HP;MDL:officejet series 300;"), "oj-300")
        self.assertEqual(lookup(rows, "MFG:HP;MDL:Thinseries;"), "thin")
        self.assertIsNone(lookup(rows, "MFG:HP;MDL:Thin;"))

    def test_entries_in_xml_comments_and_raw_and_ps_families_give_no_rows(self):
        rows = self.rows(canon='<family name="canon"><!--'
                         '<printer name="Canon iP100" manufacturer="Canon" driver="bjc-iP100"'
                         ' deviceid="MFG:Canon;MDL:iP100 series;" />'
                         "--></family>",
                         raw='<family name="raw">'
                         '<printer name="RAW DATA 8 bit" manufacturer="" driver="raw-data-8" />'
                         "</family>",
                         ps='<family name="ps">'
                         '<printer name="Adobe PostScript" manufacturer="Adobe" driver="ps"'
                         ' deviceid="MFG:Adobe;MDL:PostScript;" />'
                         "</family>")
        self.assertEqual(rows, [])

    def test_rows_keep_the_files_order_and_characters_xml_needs_escaped(self):
        rows = self.rows(b='<family name="pcl">'
                         '<printer name="HP B &amp; &quot;Q&quot; &lt;1&gt;" manufacturer="HP" driver="b" />'
                         "</family>",
                         a='<family name="canon">'
                         '<printer name="Canon A" manufacturer="Canon" driver="a" /></family>')
        self.assertEqual(rows, [("Canon", "A", "a"), ("HP", 'B & "Q" <1>', "b")])

    def test_a_data_directory_without_printer_data_fails(self):
        directory = data_with()
        self.addCleanup(lambda: subprocess.run(["rm", "-rf", directory], check=True))
        with tempfile.TemporaryDirectory() as out:
            result = subprocess.run([sys.executable, "-I", GENERATOR, directory, out],
                                    capture_output=True, timeout=60, check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn(b"no printers", result.stderr)


class DataVersion(unittest.TestCase):
    """The string that names a copy of the data: the same for the same data,
    another for any change."""

    def setUp(self):
        self.directory = data_with(canon='<family name="canon">'
                                   '<printer name="Canon A" manufacturer="Canon" driver="a" />'
                                   "</family>")
        self.addCleanup(lambda: subprocess.run(["rm", "-rf", self.directory], check=True))

    def write(self, path, text):
        os.makedirs(os.path.dirname(os.path.join(self.directory, path)), exist_ok=True)
        with open(os.path.join(self.directory, path), "w", encoding="utf-8") as f:
            f.write(text)

    def test_the_version_is_a_plain_directory_name(self):
        version = data_version(self.directory)
        self.assertRegex(version, r"^[0-9a-f]{16}$")

    def test_the_same_data_gives_the_same_version(self):
        self.assertEqual(data_version(self.directory), data_version(self.directory))

    def test_a_changed_added_or_renamed_data_file_gives_another_version(self):
        versions = [data_version(self.directory)]
        self.write("papers/a.xml", "<paper/>")
        versions.append(data_version(self.directory))
        self.write("papers/a.xml", "<paper />")
        versions.append(data_version(self.directory))
        os.rename(os.path.join(self.directory, "papers", "a.xml"),
                  os.path.join(self.directory, "papers", "b.xml"))
        versions.append(data_version(self.directory))
        self.assertEqual(len(set(versions)), 4, versions)

    def test_the_build_data_has_a_version(self):
        self.assertRegex(data_version(DATA), r"^[0-9a-f]{16}$")


if __name__ == "__main__":
    unittest.main()
