#! /bin/sh
export LD_LIBRARY_PATH=./objs/lib
export ANDROID_WINDOW_SIZE=1024x768
./objs/emulator_test_renderer 10.254.1.35
