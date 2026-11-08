#!/usr/bin/env bash
# print-engine-android: fails when a source file of this repository lacks
# its licence notice.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: check-licence-notices.sh [REPO_DIR]
#
# Every source, build or test file outside third_party/ carries a GPL
# notice: the full GPL-2.0-or-later notice in C files, the one-line
# "GPL-2.0-or-later" notice in scripts and build files. That includes new
# files not yet added to git; git-ignored build output is skipped.
# third_party/ keeps upstream's own notices.
set -euo pipefail

repo=${1:-$(cd "$(dirname "$0")/.." && pwd)}

missing=0
checked=0
while IFS= read -r -d '' file; do
  checked=$((checked + 1))
  if ! grep -q -e "GPL-2.0-or-later" -e "GNU General Public License" "$repo/$file"; then
    echo "MISSING a GPL notice: $file" >&2
    missing=1
  fi
done < <(git -C "$repo" ls-files -z --cached --others --exclude-standard -- \
  '*.c' '*.h' '*.py' '*.sh' '*.cmake' '*CMakeLists.txt' '*.toml' '*.yml' '*.kt' '*.kts' \
  ':!:third_party/**')

if [[ $missing -ne 0 ]]; then
  echo "Add the GPL-2.0-or-later notice (copy it from src/print-engine.c, or the one-line notice from CMakeLists.txt) to the files above." >&2
  exit 1
fi
echo "All $checked source files carry a GPL notice."
