#!/bin/bash

if [[ $1 = "bd" ]]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
elif [[ $1 = "br" ]]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
elif [[ $1 = "rd" ]]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    ./build/FlyBird
fi
