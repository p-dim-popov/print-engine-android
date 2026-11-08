# print-engine-android: tests of the Android program check.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# scripts/check-android-program.py reads an ELF file's headers. These tests
# write small ELF files by hand with the fields it reads and run the check
# on them.
import os
import struct
import subprocess
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
CHECK = os.path.join(HERE, "..", "scripts", "check-android-program.py")

EM_X86_64 = 62
EM_AARCH64 = 183
ET_EXEC, ET_DYN = 2, 3
PT_LOAD, PT_INTERP, PT_NOTE = 1, 3, 4
NT_ANDROID_TYPE_IDENT = 1


def android_note(api):
    name = b"Android\0"
    desc = struct.pack("<I", api) + b"r27c".ljust(64, b"\0") + b"12479018".ljust(64, b"\0")
    return struct.pack("<III", len(name), len(desc), NT_ANDROID_TYPE_IDENT) + name + desc


def elf(machine=EM_X86_64, kind=ET_DYN, interpreter=b"/system/bin/linker64\0",
        load_alignments=(0x4000, 0x4000), note=None):
    """An ELF64 file with program headers only: the interpreter, the LOAD
    segments' alignments and an Android ident note."""
    segments = []
    if interpreter is not None:
        segments.append((PT_INTERP, interpreter, 1))
    segments += [(PT_LOAD, b"", alignment) for alignment in load_alignments]
    segments.append((PT_NOTE, android_note(26) if note is None else note, 4))
    header_size, entry_size = 64, 56
    offset = header_size + entry_size * len(segments)
    headers, payload = b"", b""
    for kind_of_segment, data, alignment in segments:
        headers += struct.pack("<IIQQQQQQ", kind_of_segment, 4, offset + len(payload), 0, 0,
                               len(data), len(data), alignment)
        payload += data
    ident = b"\x7fELF" + bytes([2, 1, 1]) + bytes(9)
    header = ident + struct.pack("<HHIQQQIHHHHHH", kind, machine, 1, 0, header_size, 0, 0,
                                 header_size, entry_size, len(segments), 64, 0, 0)
    return header + headers + payload


class CheckAndroidProgram(unittest.TestCase):
    def check(self, data, abi="x86_64", api="26"):
        with tempfile.NamedTemporaryFile(suffix=".elf") as f:
            f.write(data)
            f.flush()
            return subprocess.run([sys.executable, "-I", CHECK, f.name, abi, api],
                                  capture_output=True, timeout=60, check=False)

    def assertRefused(self, result, reason):
        self.assertEqual(result.returncode, 1, result.stdout)
        self.assertIn(reason, result.stderr.decode())

    def test_a_program_for_the_abi_api_and_16_kb_pages_passes(self):
        self.assertEqual(self.check(elf()).returncode, 0)
        self.assertEqual(self.check(elf(machine=EM_AARCH64), abi="arm64-v8a").returncode, 0)
        self.assertEqual(self.check(elf(load_alignments=(0x10000,))).returncode, 0)

    def test_another_machine_is_refused(self):
        self.assertRefused(self.check(elf(machine=EM_AARCH64)), "machine")

    def test_a_program_that_is_not_position_independent_is_refused(self):
        self.assertRefused(self.check(elf(kind=ET_EXEC)), "position-independent")

    def test_a_program_for_another_loader_is_refused(self):
        self.assertRefused(self.check(elf(interpreter=b"/lib64/ld-linux-x86-64.so.2\0")),
                           "interpreter")
        self.assertRefused(self.check(elf(interpreter=None)), "interpreter")

    def test_a_segment_aligned_for_4_kb_pages_is_refused(self):
        self.assertRefused(self.check(elf(load_alignments=(0x4000, 0x1000))), "16 KB")

    def test_a_program_for_another_api_level_is_refused(self):
        self.assertRefused(self.check(elf(note=android_note(30))), "API level 30")
        self.assertRefused(self.check(elf(note=b"")), "Android note")

    def test_a_file_that_is_not_elf_is_refused(self):
        self.assertRefused(self.check(b"#!/bin/sh\n"), "not an ELF64")


if __name__ == "__main__":
    unittest.main()
