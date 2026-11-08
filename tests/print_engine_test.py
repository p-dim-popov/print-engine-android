# print-engine-android: host tests of the print-engine program.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Each test runs the program as a user of its interface does: arguments,
# STP_DATA_PATH, stdin, and then stdout, stderr and the exit code. CTest
# sets PRINT_ENGINE (the program) and STP_DATA_PATH (the data directory).
import gzip
import os
import re
import subprocess
import unittest

import pwg

PROGRAM = os.environ.get("PRINT_ENGINE", "build/print-engine")
DATA = os.environ.get("STP_DATA_PATH", "build/data")
HERE = os.path.dirname(os.path.abspath(__file__))
MP250 = "bjc-MP250-series"
RAW = "raw-data-8"
A4 = "iso_a4_210x297mm"
LETTER = "na_letter_8.5x11in"

USAGE = 2
BAD_RASTER = 3
DRIVER_FAILED = 4

# Canon's start-of-job and end-of-job blocks are IVEC XML commands.
START_JOB = b"<ivec:operation>StartJob</ivec:operation>"
END_JOB = b"<ivec:operation>EndJob</ivec:operation>"


def run(*args, stdin=b"", env=None):
    environment = {"STP_DATA_PATH": DATA} if env is None else env
    return subprocess.run([PROGRAM, *args], input=stdin, capture_output=True,
                          env=environment, timeout=120, check=False)


def print_job(driver, stdin, *options):
    args = ["print", "--driver", driver]
    for option in options:
        args += ["--option", option]
    return run(*args, stdin=stdin)


def describe(driver):
    result = run("describe", "--driver", driver)
    assert result.returncode == 0, result.stderr
    lines = result.stdout.decode().splitlines()
    pairs = [line.split("=", 1) for line in lines]
    assert all(len(pair) == 2 for pair in pairs), lines
    return pairs


def values(pairs, key):
    return [value for k, value in pairs if k == key]


def canon_bands(job):
    """The raster commands of a Canon job: the planes it names (ESC ( L) and
    the payload of each ESC ( F command, one per plane per band."""
    planes = re.search(rb"\x1b\(L(..)", job, re.DOTALL)
    count = int.from_bytes(planes.group(1), "little")
    plane_names = job[planes.end():planes.end() + count]
    payloads = []
    at = 0
    while True:
        at = job.find(b"\x1b(F", at)
        if at < 0:
            break
        length = int.from_bytes(job[at + 3:at + 5], "little")
        payloads.append(job[at + 5:at + 5 + length])
        at += 5 + length
    return plane_names, payloads


def ink(payload):
    """Whether a band's payload carries ink: an empty band codes each line as
    an empty run."""
    return any(byte not in (0x00, 0x80) for byte in payload)


class Usage(unittest.TestCase):
    def test_no_arguments_is_a_usage_error(self):
        result = run()
        self.assertEqual(result.returncode, USAGE)
        self.assertIn(b"usage", result.stderr.lower())
        self.assertEqual(result.stdout, b"")

    def test_help_goes_to_stdout(self):
        result = run("--help")
        self.assertEqual(result.returncode, 0)
        self.assertIn(b"usage", result.stdout.lower())

    def test_an_unknown_command_is_a_usage_error(self):
        self.assertEqual(run("scan", "--driver", MP250).returncode, USAGE)

    def test_a_missing_driver_is_a_usage_error(self):
        self.assertEqual(run("describe").returncode, USAGE)

    def test_an_unknown_driver_exits_with_the_usage_code(self):
        for command in ("describe", "print"):
            with self.subTest(command=command):
                result = run(command, "--driver", "no-such-printer",
                             stdin=pwg.stream(pwg.a4(75, pwg.SGRAY, 255)))
                self.assertEqual(result.returncode, USAGE)
                self.assertIn(b"no-such-printer", result.stderr)
                self.assertEqual(result.stdout, b"")

    def test_the_data_directory_comes_from_stp_data_path(self):
        result = run("describe", "--driver", MP250, env={})
        self.assertEqual(result.returncode, USAGE)
        self.assertIn(b"STP_DATA_PATH", result.stderr)
        empty = os.path.join(HERE, "data", "no-such-directory")
        result = run("describe", "--driver", MP250, env={"STP_DATA_PATH": empty})
        self.assertEqual(result.returncode, USAGE)

    def test_bad_options_are_usage_errors_and_print_nothing(self):
        page = pwg.stream(pwg.a4(75, pwg.SGRAY, 255))
        for option in ("media=no_such_paper_1x1in", "resolution=fast", "resolution=4800dpi",
                       "color-mode=sepia", "copies=2", "media"):
            with self.subTest(option=option):
                result = print_job(MP250, page, option)
                self.assertEqual(result.returncode, USAGE)
                self.assertEqual(result.stdout, b"")

    def test_describe_takes_no_options(self):
        result = run("describe", "--driver", MP250, "--option", "media=" + A4)
        self.assertEqual(result.returncode, USAGE)


class Describe(unittest.TestCase):
    def test_the_mp250_lists_a4_and_letter_by_their_pwg_names(self):
        media = values(describe(MP250), "media")
        self.assertIn(A4, media)
        self.assertIn(LETTER, media)
        self.assertIn("iso_a5_148x210mm", media)
        self.assertEqual(len(media), len(set(media)))

    def test_the_mp250_lists_its_resolutions_and_colour_modes(self):
        pairs = describe(MP250)
        self.assertIn("600dpi", values(pairs, "resolution"))
        self.assertIn("300dpi", values(pairs, "resolution"))
        self.assertEqual(values(pairs, "color-mode"), ["color", "monochrome"])

    def test_every_default_is_one_of_the_choices(self):
        for driver in (MP250, RAW, "pcl-g_5c", "escp2-c88", "ps2"):
            pairs = describe(driver)
            for key in ("media", "resolution", "color-mode"):
                with self.subTest(driver=driver, key=key):
                    defaults = values(pairs, key + "-default")
                    self.assertLessEqual(len(defaults), 1)
                    if driver != "ps2":
                        self.assertEqual(len(defaults), 1)
                    for default in defaults:
                        self.assertIn(default, values(pairs, key))
            for resolution in values(pairs, "resolution"):
                self.assertRegex(resolution, r"^[1-9][0-9]*(x[1-9][0-9]*)?dpi$")

    def test_the_data_holds_every_printer_family(self):
        # One driver of each of Gutenprint's families: Canon, Epson ESC/P2,
        # PCL, dye-sub, Lexmark, DPL label printers and raw. PostScript's
        # driver takes its papers from a PPD file, so it lists none.
        for driver in (MP250, "escp2-c88", "pcl-g_5c", "mitsubishi-p95d", "lexmark-z43",
                       "datamax_oneil_I4212e", RAW):
            with self.subTest(driver=driver):
                self.assertTrue(values(describe(driver), "media"))
        self.assertEqual(values(describe("ps2"), "driver"), ["ps2"])

    def test_the_mp250_defaults(self):
        pairs = describe(MP250)
        self.assertEqual(values(pairs, "driver"), [MP250])
        self.assertEqual(values(pairs, "model"), ["Canon MP250 series"])
        self.assertEqual(values(pairs, "media-default"), [LETTER])
        self.assertEqual(values(pairs, "resolution-default"), ["600dpi"])
        self.assertEqual(values(pairs, "color-mode-default"), ["color"])

    def test_a_paper_without_a_standard_size_gets_an_other_name(self):
        media = values(describe(MP250), "media")
        self.assertIn("oe_cd5inch_4.57x4.57in", media)
        self.assertIn("jis_b5_182x257mm", media)


class GoldenJob(unittest.TestCase):
    def test_the_test_card_gives_the_golden_mp250_job(self):
        with open(os.path.join(HERE, "data", "test-card.pwg"), "rb") as f:
            card = f.read()
        with gzip.open(os.path.join(HERE, "data", "test-card.bjc-MP250-series.prn.gz")) as f:
            golden = f.read()
        result = print_job(MP250, card, "media=" + A4, "resolution=600dpi", "color-mode=color")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(result.stdout == golden, "the job differs from the golden job")

    def test_the_golden_input_is_the_test_card(self):
        with open(os.path.join(HERE, "data", "test-card.pwg"), "rb") as f:
            self.assertEqual(f.read(), pwg.test_card())

    def test_the_job_begins_with_the_start_of_job_block_and_ends_with_end_of_job(self):
        result = print_job(MP250, pwg.stream(pwg.a4(75, pwg.SGRAY, 255)), "media=" + A4)
        self.assertEqual(result.returncode, 0, result.stderr)
        job = result.stdout
        self.assertTrue(job.startswith(b'<?xml version="1.0" encoding="utf-8" ?><cmd '), job[:64])
        self.assertIn(START_JOB, job[:400])
        self.assertIn(END_JOB, job[-400:])
        self.assertEqual(job.count(START_JOB), 1)
        self.assertEqual(job.count(END_JOB), 1)


class Coverage(unittest.TestCase):
    def test_a_white_page_gives_a_near_empty_mp250_job(self):
        result = print_job(MP250, pwg.stream(pwg.a4(150, pwg.SGRAY, 255)), "media=" + A4)
        self.assertEqual(result.returncode, 0, result.stderr)
        _, bands = canon_bands(result.stdout)
        self.assertGreater(len(bands), 0)
        self.assertFalse(any(ink(band) for band in bands))
        self.assertLess(len(result.stdout), 64 * 1024)

    def test_a_black_page_puts_ink_on_every_band_of_the_mp250_job(self):
        for space, black in ((pwg.SGRAY, 0), (pwg.SRGB, (0, 0, 0))):
            with self.subTest(space=space):
                result = print_job(MP250, pwg.stream(pwg.a4(150, space, black)), "media=" + A4)
                self.assertEqual(result.returncode, 0, result.stderr)
                planes, bands = canon_bands(result.stdout)
                self.assertEqual(planes, b"CMYK")
                groups = [bands[i:i + len(planes)] for i in range(0, len(bands), len(planes))]
                # Every band of the printable area, 6816 lines at 600 dpi.
                self.assertGreater(len(groups), 6816 // 8 - 2)
                self.assertTrue(all(any(ink(b) for b in group) for group in groups))

    def test_white_and_black_pass_through_the_raw_driver_unchanged(self):
        # raw-data-8 writes each pixel's RGB value, one pixel per point,
        # over the whole paper.
        width, height = pwg.A4_POINTS
        for space, value, expected in ((pwg.SGRAY, 255, 255), (pwg.SGRAY, 0, 0),
                                       (pwg.SRGB, (255, 255, 255), 255), (pwg.SRGB, (0, 0, 0), 0)):
            with self.subTest(space=space, value=value):
                page = pwg.solid(width, height, 72, space, value, page_size=pwg.A4_POINTS)
                result = print_job(RAW, pwg.stream(page), "media=" + A4)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual(result.stdout, bytes([expected]) * (width * height * 3))

    def test_the_raster_lands_where_it_is_on_the_page(self):
        width, height = pwg.A4_POINTS

        def row(y):
            # A black top-left quarter, a red pixel at (500, 700).
            line = bytearray(b"\xff" * (width * 3))
            if y < height // 2:
                line[0:3 * (width // 2)] = b"\x00" * (3 * (width // 2))
            if y == 700:
                line[1500:1503] = b"\xff\x00\x00"
            return bytes(line)

        page = pwg.page(width, height, 72, pwg.SRGB, row, page_size=pwg.A4_POINTS)
        result = print_job(RAW, pwg.stream(page), "media=" + A4)
        self.assertEqual(result.returncode, 0, result.stderr)
        out = result.stdout

        def pixel(x, y):
            at = 3 * (y * width + x)
            return out[at:at + 3]

        self.assertEqual(pixel(0, 0), b"\x00\x00\x00")
        self.assertEqual(pixel(width // 2 - 1, height // 2 - 1), b"\x00\x00\x00")
        self.assertEqual(pixel(width // 2, 0), b"\xff\xff\xff")
        self.assertEqual(pixel(0, height // 2), b"\xff\xff\xff")
        self.assertEqual(pixel(500, 700), b"\xff\x00\x00")


class Options(unittest.TestCase):
    page = pwg.stream(pwg.a4(150, pwg.SGRAY, 0))

    def job(self, *options):
        result = print_job(MP250, self.page, *options)
        self.assertEqual(result.returncode, 0, result.stderr)
        return result.stdout

    def test_resolution_selects_the_mode(self):
        fine = self.job("media=" + A4, "resolution=600dpi")
        coarse = self.job("media=" + A4, "resolution=300dpi")
        self.assertEqual(self.job("media=" + A4, "resolution=300x300dpi"), coarse)
        self.assertLess(len(coarse), len(fine))

    def test_media_selects_the_paper(self):
        self.assertNotEqual(self.job("media=" + A4), self.job("media=" + LETTER))

    def test_without_media_the_page_names_its_paper(self):
        # pwg.a4 names iso_a4_210x297mm in the page header; the default is Letter.
        self.assertEqual(self.job(), self.job("media=" + A4))

    def test_color_mode_selects_the_printing_mode(self):
        self.assertNotEqual(self.job("color-mode=monochrome"), self.job("color-mode=color"))


class Pages(unittest.TestCase):
    def test_pages_print_in_one_job(self):
        one = print_job(MP250, pwg.stream(pwg.a4(75, pwg.SGRAY, 0)), "media=" + A4)
        two = print_job(MP250, pwg.stream(pwg.a4(75, pwg.SGRAY, 0), pwg.a4(75, pwg.SGRAY, 0)),
                        "media=" + A4)
        self.assertEqual(two.returncode, 0, two.stderr)
        self.assertEqual(two.stdout.count(START_JOB), 1)
        self.assertEqual(two.stdout.count(END_JOB), 1)
        self.assertGreater(len(two.stdout), len(one.stdout) * 3 // 2)


class BadRaster(unittest.TestCase):
    def test_input_that_is_not_pwg_raster_exits_3_and_writes_nothing(self):
        for name, data in (("empty", b""), ("no sync word", b"%PDF-1.7\n"),
                           ("no page", b"RaS2"), ("short header", b"RaS2" + bytes(100))):
            with self.subTest(name=name):
                result = print_job(MP250, data, "media=" + A4)
                self.assertEqual(result.returncode, BAD_RASTER)
                self.assertEqual(result.stdout, b"")
                self.assertIn(b"bad raster", result.stderr)

    def test_an_unsupported_page_type_exits_3(self):
        header = bytearray(pwg.header(100, 100, 75, pwg.SGRAY))
        header[400:404] = (3).to_bytes(4, "big")  # black_1's colour space
        result = print_job(MP250, b"RaS2" + bytes(header), "media=" + A4)
        self.assertEqual(result.returncode, BAD_RASTER)
        self.assertEqual(result.stdout, b"")

    def test_a_page_cut_short_exits_3_and_still_ends_the_job(self):
        good = pwg.a4(75, pwg.SGRAY, 0)
        for name, data in (("first page", pwg.stream(good)[:-10]),
                           ("second page", pwg.stream(good, good)[:-10])):
            with self.subTest(name=name):
                result = print_job(MP250, data, "media=" + A4)
                self.assertEqual(result.returncode, BAD_RASTER)
                self.assertIn(START_JOB, result.stdout)
                self.assertIn(END_JOB, result.stdout[-400:])

    def test_a_run_past_the_end_of_its_line_exits_3(self):
        header = pwg.header(4, 1, 75, pwg.SGRAY)
        # One line of 4 pixels, coded as a run of 5.
        result = print_job(MP250, b"RaS2" + header + bytes([0, 4, 0]), "media=" + A4)
        self.assertEqual(result.returncode, BAD_RASTER)


class DriverFailure(unittest.TestCase):
    def test_a_driver_that_refuses_the_page_exits_4(self):
        # raw-data-8 needs one pixel per point; a 150 dpi page has more.
        result = print_job(RAW, pwg.stream(pwg.a4(150, pwg.SGRAY, 255)), "media=" + A4)
        self.assertEqual(result.returncode, DRIVER_FAILED)

    def test_a_closed_stdout_exits_4(self):
        read_end, write_end = os.pipe()
        os.close(read_end)
        try:
            result = subprocess.run(
                [PROGRAM, "print", "--driver", MP250, "--option", "media=" + A4],
                input=pwg.stream(pwg.a4(75, pwg.SGRAY, 0)), stdout=write_end,
                stderr=subprocess.PIPE, env={"STP_DATA_PATH": DATA}, timeout=120, check=False)
        finally:
            os.close(write_end)
        self.assertEqual(result.returncode, DRIVER_FAILED)
        self.assertIn(b"writing", result.stderr)


if __name__ == "__main__":
    unittest.main()
