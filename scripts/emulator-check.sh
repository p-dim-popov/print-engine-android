#!/usr/bin/env bash
# print-engine-android: runs the Android build of the program on an emulator
# and compares its job with the host build's golden job.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: ANDROID_SERIAL=emulator-5554 emulator-check.sh [PROGRAM]
#
# Pushes PROGRAM (default: build-android/x86_64/libprintengine.so, which
# scripts/build-android.sh builds), the data directory build/data and the
# test card (tests/data/test-card.pwg) to /data/local/tmp on the device
# ANDROID_SERIAL names, runs the program from `adb shell` as the
# golden test runs it on the host, pulls the job and compares it byte for
# byte with tests/data/test-card.bjc-MP250-series.prn.gz. The device must be
# an x86_64 emulator: the script refuses any other device, so that it never
# runs on a phone that is also on adb. It removes what it pushed.
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
program=${1:-$repo/build-android/x86_64/libprintengine.so}
data="$repo/build/data"
card="$repo/tests/data/test-card.pwg"
golden="$repo/tests/data/test-card.bjc-MP250-series.prn.gz"
remote=/data/local/tmp/print-engine-check

if [[ -z ${ANDROID_SERIAL:-} ]]; then
  echo "emulator-check.sh: set ANDROID_SERIAL to the emulator's serial (adb devices)" >&2
  exit 2
fi
for file in "$program" "$data/printers" "$card" "$golden"; do
  [[ -e $file ]] || { echo "emulator-check.sh: $file is missing; build first" >&2; exit 2; }
done
emulator=$(adb shell getprop ro.kernel.qemu | tr -d '\r')
abi=$(adb shell getprop ro.product.cpu.abi | tr -d '\r')
if [[ $emulator != 1 || $abi != x86_64 ]]; then
  echo "emulator-check.sh: $ANDROID_SERIAL is not an x86_64 emulator (ro.kernel.qemu=$emulator, abi=$abi)" >&2
  exit 2
fi

local_dir=$(mktemp -d)
cleanup() {
  adb shell rm -rf "$remote" || true
  rm -rf "$local_dir"
}
trap cleanup EXIT

adb shell rm -rf "$remote"
adb shell mkdir -p "$remote"
adb push -q "$program" "$remote/print-engine"
adb shell chmod 755 "$remote/print-engine"
adb push -q "$data" "$remote/data"
adb push -q "$card" "$remote/test-card.pwg"
status=$(adb shell "cd $remote && STP_DATA_PATH=$remote/data ./print-engine print \
  --driver bjc-MP250-series --option media=iso_a4_210x297mm --option resolution=600dpi \
  --option color-mode=color < test-card.pwg > job.prn 2> stderr.txt; echo \$?" | tr -d '\r')
adb pull -q "$remote/job.prn" "$local_dir/job.prn"
adb pull -q "$remote/stderr.txt" "$local_dir/stderr.txt"
if [[ $status != 0 ]]; then
  echo "emulator-check.sh: the program exited $status on $ANDROID_SERIAL:" >&2
  cat "$local_dir/stderr.txt" >&2
  exit 1
fi
gzip -dc "$golden" > "$local_dir/golden.prn"
if ! cmp "$local_dir/golden.prn" "$local_dir/job.prn"; then
  echo "emulator-check.sh: the job on $ANDROID_SERIAL differs from the golden job" >&2
  exit 1
fi
echo "The job on $ANDROID_SERIAL ($(wc -c < "$local_dir/job.prn") bytes, sha256" \
  "$(sha256sum < "$local_dir/job.prn" | cut -d' ' -f1)) is the golden job."
