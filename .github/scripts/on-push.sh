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

	BOARD="esp8285"
	mkdir -p $HOME/.pioenvs
	export PLATFORMIO_ENVS_DIR=$HOME/.pioenvs
	export PLATFORMIO_CI_SRC="/Users/runner/work/Corgi85/Corgi85"
	python -m platformio lib --storage-dir "$PLATFORMIO_CI_SRC" install
	# platformio ci --lib="." --project-conf=./platformio.ini src/Corgi85
	platformio ci -l '.' --build-dir="$HOME/.pioenvs" --keep-build-dir --board "$BOARD" "$GITHUB_WORKSPACE" 
fi