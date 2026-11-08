# print-engine-android

A command-line printing tool over [Gutenprint](https://gimp-print.sourceforge.io/): PWG Raster pages in, a printer's own bytes out. It builds and is tested on Linux. It is written to build for Android (NDK) as well, where a program can run it as a separate process for one print job; that build is not in this repository yet.

The tool is one program, `print-engine`, with two commands: `describe` lists a printer driver's choices, and `print` turns pages into a print job for that driver. It knows nothing of USB, of a print spooler or of the platform it runs on: it reads its arguments, its environment and stdin, and writes stdout and stderr. The caller sends the job's bytes to the printer.

## Licence

GPL-2.0-or-later. See [COPYING](COPYING) and the notice at the top of each file. Imported code keeps its own notices:

| Directory | Version | Licence |
|---|---|---|
| `third_party/gutenprint` | 5.3.5, unchanged (see below) | GPL-2.0-or-later |

## The interface

```
print-engine describe --driver NAME
print-engine print --driver NAME [--option KEY=VALUE]...
print-engine --help
```

`-h` is the same as `--help`.

`NAME` is a Gutenprint driver name, such as `bjc-MP250-series` for the Canon PIXMA MP250 or `escp2-c88` for the Epson Stylus C88. Gutenprint's printer data lists the drivers (`printers/*.xml` in the data directory, attribute `driver`); entries inside XML comments are not loaded, so their names are unknown drivers.

The environment variable `STP_DATA_PATH` names Gutenprint's data directory, the one the build makes (see "How it is built"). The program has no compiled-in data directory: without `STP_DATA_PATH` it refuses to run.

Messages go to stderr, in English: the program's own, which start with `print-engine:`, and Gutenprint's. stdout carries only the output the command describes below.

### Exit codes

| Code | Meaning |
|---|---|
| 0 | Success. |
| 2 | Usage error: an unknown command, argument or option, a missing `--driver`, an option value that the driver does not offer, no `STP_DATA_PATH`, or an unknown driver (also when the data directory holds no printer data). Nothing is written to stdout. |
| 3 | Bad raster: stdin is not a PWG Raster stream that the program takes, or it ends early. |
| 4 | Driver or output failure: the driver refused the settings or failed on a page, or writing stdout failed (a closed pipe included). |

### describe

`describe` writes the driver's choices on stdout, one `KEY=VALUE` per line, and exits 0. A key that has several values has one line per value, in the driver's order. The keys:

| Key | Value |
|---|---|
| `driver` | The driver name. |
| `model` | The printer's make and model, as Gutenprint names it (`Canon MP250 series`). |
| `media` | A paper the driver offers, as a PWG media name (PWG 5101.1), such as `iso_a4_210x297mm` or `na_letter_8.5x11in`. |
| `media-default` | The driver's default paper. |
| `resolution` | A resolution the driver prints at: `600dpi`, or `720x360dpi` when the two directions differ. |
| `resolution-default` | The resolution of the driver's default print mode. |
| `color-mode` | `color` or `monochrome`, each when the driver offers it. |
| `color-mode-default` | The driver's default colour mode, when it is one of the `color-mode` values. |

A paper gets the standard PWG name of its size when there is one, within a millimetre. Otherwise it gets a self-describing name of the class `om` (metric papers) or `oe` (the others): its Gutenprint name in lower case, then its size, as `oe_cd5inch_4.57x4.57in`. Papers of one size share a name, and the first of them in the driver's order stands for the size. Sizes the user sets (Gutenprint's `Custom`) and roll papers are not listed.

A driver that does not report a key lists no line for it; the PostScript drivers, for example, take their papers from a PPD file and list no `media`. A consumer ignores keys it does not know: later versions may add keys.

### print

`print` reads one PWG Raster stream on stdin and writes the job for the printer on stdout, as the driver produces it. The caller copies stdout to the printer.

The input is PWG Raster (PWG 5102.4): the sync word `RaS2`, then each page as a 1796-byte page header followed by the page's lines in PWG Raster's run-length code. The program takes 8-bit pages only, `sgray_8` (colour space 18, one colour) and `srgb_8` (colour space 19, three colours, chunky). A stream needs at least one page; the pages of one stream may differ in size, resolution and colour space.

The options:

| Option | Values | Without the option |
|---|---|---|
| `media=NAME` | A `media` value of `describe`. | The paper the page header names (its `PageSizeName`, if the driver offers that paper), else the paper whose size matches the header's `PageSize` within a point, else the driver's default. |
| `resolution=VALUE` | A `resolution` value of `describe`; also `600x600dpi` for `600dpi`, or `600`. Any other resolution is a usage error. | The driver's default print mode. |
| `color-mode=VALUE` | A `color-mode` value of `describe`. | The driver's default colour mode. |

When an option is given twice, the last one counts. `media` holds for every page of the stream. The page's `HWResolution` need not be the printer's resolution: most drivers scale the page to the resolution the job prints at. A few take only one pixel per point (the `raw-data-8` and `raw-data-16` drivers) and refuse other pages with exit code 4.

What the program does with these:

- **Print mode.** Gutenprint drivers print in named modes, each with a resolution and the colour modes it offers. The program takes the driver's default mode when it has the chosen resolution and colour mode, else the first mode in the driver's order that has both. When no mode has both, the colour mode wins: the program takes the mode with that colour mode whose resolution is nearest the chosen one (the MP250's 1200 dpi modes are colour only, so `resolution=1200dpi` with `color-mode=monochrome` prints at 600 dpi). So every `resolution` value prints with every `color-mode` value. A driver may then replace the mode with one that suits the paper type; Canon's drivers do. Where a driver has several modes at one resolution (Canon's draft, standard and high quality modes), `resolution` reaches only the default one, or the first one; the program offers no quality presets apart from resolutions.
- **Placement.** A page's raster covers the whole sheet: its top left pixel is the paper's top left corner, at the page's `HWResolution`. The program sends the driver the part of the raster that lies inside the driver's printable area for the paper, in place. Pixels outside it are dropped, and where the raster is smaller than the printable area, the rest is white.
- **One job.** All pages of the stream print in one job. The job is wrapped in the driver's start-of-job and end-of-job blocks (Gutenprint's `stp_start_job` and `stp_end_job`). For Canon's IVEC printers the start-of-job block is the `StartJob` XML command, without which a printer such as the MP250 ignores the whole job.
- **Failures after the start.** If the raster turns out bad, or the driver fails, after the job has started, the program still writes the end-of-job block, so that a printer is not left in the middle of a job, and then exits 3 or 4. The job then holds the pages before the failing one and the part of the failing page that the driver had written, which the driver ends as a page: a printer may print and eject that partial page.
- **Streaming.** The job's bytes are written as the driver makes them, page by page, so the caller can send them while later pages are still read.
- **Stopping.** The program ignores SIGPIPE, so that a closed stdout fails the job with exit code 4, and handles no other signal. Killing it ends the job where it is; a caller that does so must stop sending the job to the printer.
- **Copies.** The program prints each page of the stream once. A caller that wants copies sends the pages again.

Example: a job for the MP250 on A4, in monochrome:

```
STP_DATA_PATH=build/data build/print-engine print --driver bjc-MP250-series \
  --option media=iso_a4_210x297mm --option resolution=600dpi \
  --option color-mode=monochrome < pages.pwg > job.prn
```

## Layout

- `third_party/gutenprint`: the Gutenprint 5.3.5 release.
- `CMakeLists.txt`: the build; `cmake/Gutenprint.cmake`: libgutenprint as a static library.
- `src/print-engine.c`: the program. `src/pwg-raster.c`: the PWG Raster reader. `src/pwg-media.c`: PWG media names for Gutenprint's papers. `src/gutenprint-config/config.h`: Gutenprint's `config.h`, written by hand.
- `scripts/build-data.py`: the data step. `scripts/import-upstream.sh`: imports an upstream release. `scripts/check-licence-notices.sh`: the licence guard.
- `tests/`: the host tests (Python `unittest`, run by CTest) and their data.

## How it is built

CMake builds libgutenprint from its sources as a static library, with every family driver and the colour module linked in, as `configure --with-modules=static --without-cups --disable-nls` builds it. Gutenprint's `config.h` is written by hand for glibc and bionic; `gutenprint-version.h` is made from its `.in` file. The program links that library and nothing else but libm, so it needs no CUPS and no PPD files. When this build was written, the test card's job (see "Tests") was checked once by hand against the same program linked with libgutenprint from upstream's own autotools build (`configure --with-modules=static --without-cups`, Linux x86_64, GCC 13): the bytes were the same. No test repeats that check.

The data step, `scripts/build-data.py`, builds the data directory in `build/data`: every file that a `Makefile.am` under Gutenprint's `src/xml` installs, at the same path, for every printer family (Canon, Epson ESC/P2, PCL, dye-sub, Lexmark, DPL, PostScript, raw). Upstream's build copies these XML files unchanged and builds nothing else the library reads, so `build/data` is the same tree as upstream's `make install` writes to `share/gutenprint/5.3/xml` (checked with `diff -r` when the step was written). The data is the same on every architecture, so a cross build can pack the host's copy. The step fails when a Makefile installs into an unexpected directory or an XML file is installed by none, so an upstream change in layout fails the build instead of shipping less data. The CMake build runs upstream's check for duplicate printer entries as a test.

`mise.toml` pins CMake, Ninja, shellcheck, ruff and actionlint and defines a mise task for each step: `mise tasks` lists them, and `mise run <name>` runs one with the pinned tools on the PATH. A mise task runs the ones it needs first, so `mise run test` also configures and builds. `mise run lint` runs shellcheck on `scripts/`, ruff on the Python files and actionlint on the CI workflow; any finding fails it. `mise run ci` runs the same steps as CI, in the same order. The host build also needs a C compiler and Python 3.

## Tests

`tests/print_engine_test.py` runs the built program through its interface only: arguments, `STP_DATA_PATH`, stdin, and then stdout, stderr and the exit code. `tests/pwg.py` writes the PWG Raster pages it feeds in. The tests check:

- the golden job: the test card (`tests/data/test-card.pwg`, an A4 sRGB page at 150 dpi that `tests/pwg.py` writes) printed for `bjc-MP250-series` on A4 at 600 dpi in colour gives exactly the bytes of `tests/data/test-card.bjc-MP250-series.prn.gz`, gzip-compressed;
- every MP250 job begins with the IVEC `StartJob` block and ends with `EndJob`, once each, also for several pages;
- polarity and coverage: a white page gives an MP250 job with no ink in any band, under 64 KiB; a black page, grey or RGB, puts ink in every band of the printable area; through the `raw-data-8` driver, which writes each pixel's RGB value, white and black pages come out as all 255 and all 0, and a raster's pixels come out where they are on the page;
- `describe` lists the MP250's A4, Letter and A5 by their PWG names, its 600 and 300 dpi, both colour modes and its defaults, and every default is one of the choices; the data holds a driver of every family;
- the options change the job (resolution, paper, colour mode), every listed resolution prints with every listed colour mode, an unlisted resolution is a usage error, and without `media` the page header's paper is used;
- the exit codes: 2 for usage errors, an unknown driver and no data directory, with nothing on stdout; 3 for input that is not PWG Raster, an unsupported page type, a run past its line and a page cut short (the last two still end the job); 4 for a driver that refuses the page and for a closed stdout.

`tests/guard_test.py` checks the licence guard. A change that alters the golden job on purpose, such as a Gutenprint update, makes a new golden file from the test card:

```
STP_DATA_PATH=build/data build/print-engine print --driver bjc-MP250-series \
  --option media=iso_a4_210x297mm --option resolution=600dpi --option color-mode=color \
  < tests/data/test-card.pwg | gzip -9 -n > tests/data/test-card.bjc-MP250-series.prn.gz
```

## Licence guard

CI fails when a source, build or test file outside `third_party/` (`.c`, `.h`, `.py`, `.sh`, `.cmake`, `CMakeLists.txt`, `.toml`, `.yml`, `.kt`, `.kts`), committed or not yet added to git, has no GPL notice: `scripts/check-licence-notices.sh`. Git-ignored build output is skipped.

## Changes to Gutenprint 5.3.5

The first commit after the repository's start imports the release tarball unchanged, so `git log -p third_party/` shows every change. There is none so far: the host build compiles the release as it is, and the build files, `config.h` and the data step live outside `third_party/`.

## Updating upstream

1. `scripts/import-upstream.sh gutenprint <unpacked release>` replaces `third_party/gutenprint` and stages it. A plain `git add` drops the files that upstream's own `.gitignore` files match; the script adds them all and fails if any is missing.
2. Commit the import alone, in its own pull request.
3. Reapply the changes above, if any, each in its own commit. Bring `cmake/Gutenprint.cmake` and `src/gutenprint-config/config.h` up to the new `Makefile.am` and `configure.ac`, make a new golden file, and run `mise run ci`.

## Working on it

Changes reach `main` by pull request, squash-merged. Every new source file starts with the notice in `src/print-engine.c`, and build and test files carry the one-line notice used in `CMakeLists.txt`. This repository is public: its commits, comments and docs name no product or company that uses it.
