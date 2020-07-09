#!/bin/bash

set -e

if [ ! -z "$TRAVIS_BUILD_DIR" ]; then
	export GITHUB_WORKSPACE="$TRAVIS_BUILD_DIR"
	export GITHUB_REPOSITORY="$TRAVIS_REPO_SLUG"
elif [ -z "$GITHUB_WORKSPACE" ]; then
	export GITHUB_WORKSPACE="$PWD"
fi

TARGET_PLATFORM="$1"
CHUNK_INDEX=$2
CHUNKS_CNT=$3

BUILD_PIO=1

if [ "$BUILD_PIO" -eq 0 ]; then
	# ArduinoIDE Test
	echo "1"
else
	# PlatformIO Test
	source ./.github/scripts/install-platformio.sh

	python -m platformio lib --storage-dir "$GITHUB_WORKSPACE" install
	find "$GITHUB_WORKSPACE"
	BOARD="esp8285"
	# build_pio_sketch "$BOARD" "$GITHUB_WORKSPACE"
	python -m platformio ci --board "$BOARD" "$GITHUB_WORKSPACE" 
fi
