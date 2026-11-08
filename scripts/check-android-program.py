#!/usr/bin/env python3
# print-engine-android: checks a program that the NDK built for Android.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: check-android-program.py PROGRAM ABI API_LEVEL
#
# Passes (exit 0) when PROGRAM is a 64-bit ELF program for ABI (arm64-v8a or
# x86_64): position-independent, started by Android's /system/bin/linker64,
# every LOAD segment aligned for 16 KB pages (a multiple of 16384), built for
# API_LEVEL (the NDK's Android ident note), and needing no shared library
# but libc, libm and libdl. Each failed check is a line on stderr, and the
# exit code is 1; 2 is a usage error.
import struct
import sys

MACHINES = {"arm64-v8a": 183, "x86_64": 62}
ET_DYN = 3
PT_LOAD, PT_DYNAMIC, PT_INTERP, PT_NOTE = 1, 2, 3, 4
DT_NULL, DT_NEEDED, DT_STRTAB = 0, 1, 5
LIBRARIES = {"libc.so", "libm.so", "libdl.so"}
NT_ANDROID_TYPE_IDENT = 1
INTERPRETER = b"/system/bin/linker64"
PAGE = 16384


class Truncated(Exception):
    pass


def segments(data):
    """(type, file offset, address, file bytes, alignment) of each program
    header."""
    phoff, = struct.unpack_from("<Q", data, 32)
    phentsize, phnum = struct.unpack_from("<HH", data, 54)
    found = []
    for index in range(phnum):
        at = phoff + index * phentsize
        if at + 56 > len(data):
            raise Truncated
        kind, _, offset, address, _, size, _, align = struct.unpack_from("<IIQQQQQQ", data, at)
        if offset + size > len(data):
            raise Truncated
        found.append((kind, offset, address, data[offset:offset + size], align))
    return found


def needed_libraries(data, headers):
    """The DT_NEEDED names of the dynamic section."""
    entries = []
    for kind, _, _, content, _ in headers:
        if kind == PT_DYNAMIC:
            for at in range(0, len(content) - 15, 16):
                tag, value = struct.unpack_from("<QQ", content, at)
                if tag == DT_NULL:
                    break
                entries.append((tag, value))
    strtab = next((value for tag, value in entries if tag == DT_STRTAB), None)
    if strtab is None:
        return []
    base = next((offset + strtab - address for kind, offset, address, content, _ in headers
                 if kind == PT_LOAD and address <= strtab < address + len(content)), None)
    if base is None:
        raise Truncated
    names = []
    for tag, value in entries:
        if tag == DT_NEEDED:
            end = data.find(b"\0", base + value)
            if end < 0:
                raise Truncated
            names.append(data[base + value:end].decode(errors="replace"))
    return names


def android_api_levels(note):
    """The API levels of the Android ident notes in a PT_NOTE segment."""
    at = 0
    while at + 12 <= len(note):
        namesz, descsz, kind = struct.unpack_from("<III", note, at)
        name_at = at + 12
        desc_at = name_at + (namesz + 3) // 4 * 4
        if note[name_at:name_at + namesz] == b"Android\0" and kind == NT_ANDROID_TYPE_IDENT \
                and descsz >= 4:
            yield struct.unpack_from("<I", note, desc_at)[0]
        at = desc_at + (descsz + 3) // 4 * 4


def problems(data, abi, api):
    if data[:4] != b"\x7fELF" or data[4:6] != bytes([2, 1]) or len(data) < 64:
        return ["not an ELF64 little-endian file"]
    found = []
    kind, machine = struct.unpack_from("<HH", data, 16)
    if machine != MACHINES[abi]:
        found.append(f"machine {machine}, not {abi}'s {MACHINES[abi]}")
    if kind != ET_DYN:
        found.append("not a position-independent executable")
    try:
        headers = segments(data)
        needed = needed_libraries(data, headers)
    except Truncated:
        return found + ["truncated: a program header or segment lies past the end of the file"]
    interpreters = [content.rstrip(b"\0") for k, _, _, content, _ in headers if k == PT_INTERP]
    if interpreters != [INTERPRETER]:
        found.append(f"interpreter {interpreters}, not {INTERPRETER.decode()}")
    loads = [align for k, _, _, _, align in headers if k == PT_LOAD]
    if not loads or any(align == 0 or align % PAGE for align in loads):
        found.append(f"LOAD alignments {[hex(a) for a in loads]}, not 16 KB pages")
    levels = [level for k, _, _, content, _ in headers if k == PT_NOTE
              for level in android_api_levels(content)]
    if not levels:
        found.append("no Android note")
    else:
        found.extend(f"API level {level}, not {api}" for level in levels if level != api)
    others = [name for name in needed if name not in LIBRARIES]
    if others:
        found.append(f"needs {others}; only {sorted(LIBRARIES)} are allowed")
    return found


def main(argv):
    if len(argv) != 4 or argv[2] not in MACHINES or not argv[3].isdigit():
        sys.stderr.write("usage: check-android-program.py PROGRAM arm64-v8a|x86_64 API_LEVEL\n")
        return 2
    with open(argv[1], "rb") as f:
        data = f.read()
    found = problems(data, argv[2], int(argv[3]))
    for problem in found:
        sys.stderr.write(f"check-android-program.py: {argv[1]}: {problem}\n")
    if found:
        return 1
    print(f"{argv[1]}: {argv[2]}, API level {argv[3]}, PIE, linker64, 16 KB LOAD alignment,"
          " libc, libm and libdl only")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
