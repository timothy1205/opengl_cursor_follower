#!/bin/bash

cmake -S . -B cmake-build-debug "$@" || exit 1
make -C ./cmake-build-debug || exit 1
./cmake-build-debug/opengl_cursor_follower --debug-background


