#!/bin/bash

set -o errexit
SCRIPT="$(readlink -f -- ${BASH_SOURCE[0]})"
SCRIPT_DIR=$(dirname "$(readlink -f -- ${BASH_SOURCE[0]})")

echo "Running succes test 1"

datadir=$1
build="../build/apps/"

command="$build/waveform-compare $datadir/P1_1800_2000_031001_001.mp3.ffmpeg.wav $datadir/P1_1800_2000_031001_001.mp3.mpg321.wav --verbose"

echo "Execution \"$command\" on $(hostname)"

$command > "$(basename --suffix=sh "$SCRIPT")"log


echo "Test passed"

