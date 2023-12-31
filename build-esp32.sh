#!/usr/bin/env bash

set -euo pipefail
export IDF_PATH="/BuildEspAsLibrary/external_components/esp-idf"
PARAM=""

# # Retrive the target from the current filename, if no target specified,
# # the variable will be empty
# TARGET=$(echo $0 | cut -s -f2 -d- | cut -s -f1 -d.)
# if [[ -n $TARGET ]]
# then
#     # Target is not null, specify the build parameters
#     PARAM="-DCMAKE_TOOLCHAIN_FILE=$IDF_PATH/tools/cmake/toolchain-${TARGET}.cmake -DTARGET=${TARGET}"
# fi

## Install prerequsites first

# rm -rf build &&
mkdir -p build && cd build
cmake .. $PARAM
cmake --build . --verbose
