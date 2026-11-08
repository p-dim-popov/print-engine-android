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
PT_LOAD, PT_DYNAMIC, PT_INTERP, PT_NOTE = 1, 2, 3, 4
DT_NULL, DT_NEEDED, DT_STRTAB = 0, 1, 5
NT_ANDROID_TYPE_IDENT = 1


def android_note(api):
    name = b"Android\0"
    desc = struct.pack("<I", api) + b"r27c".ljust(64, b"\0") + b"12479018".ljust(64, b"\0")
    return struct.pack("<III", len(name), len(desc), NT_ANDROID_TYPE_IDENT) + name + desc


def elf(machine=EM_X86_64, kind=ET_DYN, interpreter=b"/system/bin/linker64\0",
        load_alignments=(0x4000, 0x4000), note=None, needed=("libm.so", "libdl.so", "libc.so")):
    """An ELF64 file with program headers only: the interpreter, the LOAD
    segments' alignments (the first holds the dynamic string table), an
    Android ident note and the dynamic section's needed libraries. Each
    segment's address is its file offset."""
    strings = b"\0" + b"".join(name.encode() + b"\0" for name in needed)
    count = (interpreter is not None) + len(load_alignments) + 2
    offset = 64 + 56 * count
    segments = []
    if interpreter is not None:
        segments.append((PT_INTERP, interpreter, 1))
    strtab = offset + sum(len(data) for _, data, _ in segments)
    segments += [(PT_LOAD, strings if index == 0 else b"", alignment)
                 for index, alignment in enumerate(load_alignments)]
    segments.append((PT_NOTE, android_note(26) if note is None else note, 4))
    dynamic, at = b"", 1
    for name in needed:
        dynamic += struct.pack("<QQ", DT_NEEDED, at)
        at += len(name) + 1
    dynamic += struct.pack("<QQQQ", DT_STRTAB, strtab, DT_NULL, 0)
    segments.append((PT_DYNAMIC, dynamic, 8))
    headers, payload = b"", b""
    for kind_of_segment, data, alignment in segments:
        at = offset + len(payload)
        headers += struct.pack("<IIQQQQQQ", kind_of_segment, 4, at, at, at,
                               len(data), len(data), alignment)
        payload += data
    ident = b"\x7fELF" + bytes([2, 1, 1]) + bytes(9)
    header = ident + struct.pack("<HHIQQQIHHHHHH", kind, machine, 1, 0, 64, 0, 0,
                                 64, 56, len(segments), 64, 0, 0)
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

    def test_a_segment_without_an_alignment_is_refused(self):
        self.assertRefused(self.check(elf(load_alignments=(0x4000, 0))), "16 KB")

    def test_a_truncated_file_is_refused(self):
        self.assertRefused(self.check(elf()[:80]), "truncated")

    def test_a_program_that_needs_another_library_is_refused(self):
        self.assertEqual(self.check(elf(needed=("libc.so",))).returncode, 0)
        self.assertRefused(self.check(elf(needed=("libc.so", "libc++_shared.so"))),
                           "libc++_shared.so")

    def test_a_program_for_another_api_level_is_refused(self):
        self.assertRefused(self.check(elf(note=android_note(30))), "API level 30")
        self.assertRefused(self.check(elf(note=b"")), "Android note")

    def test_a_file_that_is_not_elf_is_refused(self):
        self.assertRefused(self.check(b"#!/bin/sh\n"), "not an ELF64")


if __name__ == "__main__":
    unittest.main()
