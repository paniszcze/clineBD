#!/usr/bin/env bash

set -xe

CFLAGS="-O3 -Wall -Wextra `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib`"

mkdir -p ./build

clang $CFLAGS -o ./build/clineBD clineBD.c ./modules/gui/gui.c ./modules/gui/utils.c $LIBS