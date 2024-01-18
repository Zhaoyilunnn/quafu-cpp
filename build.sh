#!/bin/bash

BUILD_DIR=build

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}
cmake ..
make -j 16
cd -
