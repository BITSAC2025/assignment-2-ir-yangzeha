#!/bin/bash

rm -rf build/

# shellcheck disable=SC2164
mkdir build && cd build/

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
