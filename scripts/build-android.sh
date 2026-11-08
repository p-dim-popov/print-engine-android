#!/usr/bin/env bash
# print-engine-android: builds the program with the Android NDK and checks it.
# Copyright (C) 2026 Petar Popov
# GPL-2.0-or-later; see README.md and COPYING.
#
# Usage: build-android.sh [ABI]...
#        build-android.sh --ndk-version
#
# Builds build-android/<ABI>/libprintengine.so, the program, for each ABI
# (default: arm64-v8a and x86_64) with CMake and the NDK's toolchain file,
# as the Android library module's build does: API level 26, no C++
# runtime, linked for 16 KB pages, Release. Then scripts/check-android-program.py checks each
# program. The NDK is the version android/build.gradle.kts names, under
# $ANDROID_HOME/ndk (ANDROID_NDK_ROOT is not read: CI runners set it to
# their default NDK); --ndk-version prints that version and exits.
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
api=26
ndk_version=$(sed -n 's/^ *ndkVersion = "\(.*\)"$/\1/p' "$repo/android/build.gradle.kts")
if [[ -z $ndk_version ]]; then
  echo "build-android.sh: no ndkVersion in android/build.gradle.kts" >&2
  exit 1
fi
if [[ ${1:-} == --ndk-version ]]; then
  echo "$ndk_version"
  exit 0
fi
ndk=${ANDROID_HOME:?ANDROID_HOME must name the Android SDK}/ndk/$ndk_version
if ! grep -q "^Pkg.Revision = $ndk_version\$" "$ndk/source.properties" 2>/dev/null; then
  echo "build-android.sh: $ndk is not NDK $ndk_version (install it: sdkmanager \"ndk;$ndk_version\")" >&2
  exit 1
fi

abis=("$@")
[[ ${#abis[@]} -gt 0 ]] || abis=(arm64-v8a x86_64)
for abi in "${abis[@]}"; do
  build="$repo/build-android/$abi"
  # The NDK's toolchain file asks for an old CMake policy level; -Wno-deprecated
  # keeps CMake's notice about it out of the log.
  cmake -S "$repo" -B "$build" -G Ninja -Wno-deprecated \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE="$ndk/build/cmake/android.toolchain.cmake" \
    -DANDROID_ABI="$abi" \
    -DANDROID_PLATFORM="android-$api" \
    -DANDROID_STL=none \
    -DANDROID_SUPPORT_FLEXIBLE_PAGE_SIZES=ON
  cmake --build "$build" --target print-engine
  python3 -I "$repo/scripts/check-android-program.py" "$build/libprintengine.so" "$abi" "$api"
done
