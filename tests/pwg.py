# print-engine-android: a PWG Raster writer for the host tests.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Writes PWG Raster (PWG 5102.4) streams: the "RaS2" sync word, then per page
# a 1796-byte header and the rows, each line run-length encoded.
import struct

SGRAY = 18
SRGB = 19
HEADER_SIZE = 1796


def header(width, height, dpi, color_space, page_size=None, media_name="", total_pages=1):
    """A page header; page_size is (width, height) in points, from the pixels by default."""
    channels = 3 if color_space == SRGB else 1
    if page_size is None:
        page_size = (round(width * 72 / dpi), round(height * 72 / dpi))
    h = bytearray(HEADER_SIZE)
    h[0:9] = b"PwgRaster"

    def u32(offset, value):
        struct.pack_into(">I", h, offset, value)

    u32(276, dpi)  # HWResolution
    u32(280, dpi)
    u32(340, 1)  # NumCopies
    u32(352, page_size[0])  # PageSize, points
    u32(356, page_size[1])
    u32(372, width)
    u32(376, height)
    u32(384, 8)  # BitsPerColor
    u32(388, 8 * channels)  # BitsPerPixel
    u32(392, width * channels)  # BytesPerLine
    u32(396, 0)  # ColorOrder: chunky
    u32(400, color_space)
    u32(420, channels)  # NumColors
    u32(452, total_pages)  # TotalPageCount
    name = media_name.encode("ascii")
    h[1732:1732 + len(name)] = name
    return bytes(h)


def encode_line(line, bpp):
    """One line's pixels in the PWG run-length code (repeat runs and literal runs)."""
    pixels = [line[i:i + bpp] for i in range(0, len(line), bpp)]
    out = bytearray()
    i = 0
    while i < len(pixels):
        run = 1
        while i + run < len(pixels) and run < 128 and pixels[i + run] == pixels[i]:
            run += 1
        if run > 1:
            out.append(run - 1)
            out += pixels[i]
            i += run
            continue
        start = i
        i += 1
        while i < len(pixels) and i - start < 128 and not (
            i + 1 < len(pixels) and pixels[i + 1] == pixels[i]
        ):
            i += 1
        count = i - start
        out.append(0 if count == 1 else 257 - count)
        for p in pixels[start:i]:
            out += p
    return bytes(out)


def encode_rows(rows, bpp):
    """Rows (bytes each) with equal neighbours merged into one line-repeat record."""
    out = bytearray()
    i = 0
    while i < len(rows):
        repeat = 1
        while i + repeat < len(rows) and repeat < 256 and rows[i + repeat] == rows[i]:
            repeat += 1
        out.append(repeat - 1)
        out += encode_line(rows[i], bpp)
        i += repeat
    return bytes(out)


def page(width, height, dpi, color_space, row, **header_args):
    """One page: row(y) gives the bytes of line y."""
    bpp = 3 if color_space == SRGB else 1
    rows = [row(y) for y in range(height)]
    for r in rows:
        assert len(r) == width * bpp
    return header(width, height, dpi, color_space, **header_args) + encode_rows(rows, bpp)


def stream(*pages):
    return b"RaS2" + b"".join(pages)


def solid(width, height, dpi, color_space, value, **header_args):
    """A page of one colour: value is a grey level or an (r, g, b) triple."""
    pixel = bytes(value) if color_space == SRGB else bytes([value])
    line = pixel * width
    return page(width, height, dpi, color_space, lambda y: line, **header_args)


# A4 and Letter in points, as PWG 5101.1 sizes them.
A4_POINTS = (595, 842)
LETTER_POINTS = (612, 792)


def a4(dpi, color_space, value):
    """A white, black or coloured A4 page at dpi."""
    width = round(210 / 25.4 * dpi)
    height = round(297 / 25.4 * dpi)
    return solid(width, height, dpi, color_space, value, page_size=A4_POINTS,
                 media_name="iso_a4_210x297mm")


def test_card():
    """The fixed input of the golden tests: an A4 sRGB page at 150 dpi, white,
    with a black frame 2 mm to 6 mm from the edges (across the edges of a
    typical printable area), a grey ramp and red, green and blue squares."""
    dpi = 150
    width = round(210 / 25.4 * dpi)
    height = round(297 / 25.4 * dpi)
    mm = dpi / 25.4
    white = bytes([255, 255, 255])

    def row(y):
        line = bytearray(white * width)

        def fill(x0, x1, colour):
            for x in range(int(x0), int(x1)):
                line[3 * x:3 * x + 3] = colour

        if 2 * mm <= y < 6 * mm or height - 6 * mm <= y < height - 2 * mm:
            fill(2 * mm, width - 2 * mm, bytes([0, 0, 0]))
        if 2 * mm <= y < height - 2 * mm:
            fill(2 * mm, 6 * mm, bytes([0, 0, 0]))
            fill(width - 6 * mm, width - 2 * mm, bytes([0, 0, 0]))
        if 40 * mm <= y < 45 * mm:
            for x in range(int(30 * mm), int(180 * mm)):
                level = int(255 * (x - 30 * mm) / (150 * mm))
                line[3 * x:3 * x + 3] = bytes([level] * 3)
        if 60 * mm <= y < 70 * mm:
            fill(30 * mm, 40 * mm, bytes([255, 0, 0]))
            fill(50 * mm, 60 * mm, bytes([0, 255, 0]))
            fill(70 * mm, 80 * mm, bytes([0, 0, 255]))
        return bytes(line)

    return stream(page(width, height, dpi, SRGB, row, page_size=A4_POINTS,
                       media_name="iso_a4_210x297mm"))


if __name__ == "__main__":
    import sys

    # python3 tests/pwg.py > tests/data/test-card.pwg writes the golden input.
    sys.stdout.buffer.write(test_card())
