#!/bin/bash

if [[ $@ == *--build* ]]; then
    echo "Building..."
    ./build.linux.sh
    if [[ $? -ne 0 ]]; then
        echo "Build failed!"
        exit 1
    fi
fi

pushd ./build/Sandbox
./Sandbox
popd


