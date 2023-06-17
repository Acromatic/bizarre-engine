#!/bin/bash

if [[ $@ == *--clean* ]]; then
    echo "Cleaning build directory"
    rm -rf ./build
    rm -rf ./.cache
fi

OVERRIDES_FILEPATH=$(pwd)/ClangOverrides.cmake

OVERRIDES_FLAG="-DCMAKE_TOOLCHAIN_FILE=${OVERRIDES_FILEPATH}"

TOOLCHAIN_FLAGS="${OVERRIDES_FLAG} -D_CMAKE_TOOLCHAIN_PREFIX=llvm-"

COMPILER_FLAGS="-DCMAKE_CXX_COMPILER=clang++"
GENERATOR_FLAG="-G Ninja"

BUILD_TYPE=Debug
if [[ $@ == *--release* ]]; then
    BUILD_TYPE=Release
fi

cmake $GENERATOR_FLAG $TOOLCHAIN_FLAGS $COMPILER_FLAGS -DCMAKE_BUILD_TYPE=$BUILD_TYPE -B ./build -S .
cmake --build ./build -j8


