#!/bin/bash

BUILD_DIR=build

QUAFU_BIN_DIR=${HOME}/.quafu/bin

mkdir -p ${BUILD_DIR}
mkdir -p ${QUAFU_BIN_DIR}

cd ${BUILD_DIR}
cmake .. -DBUILD_QUAFU_TEST=On
make -j 16
make test

cp quafu++ ${QUAFU_BIN_DIR}

cd -
