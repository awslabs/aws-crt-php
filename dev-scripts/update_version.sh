#!/usr/bin/env bash

set -ex

BASENAME=${0}
TOOLS_DIR=$(dirname ${BASENAME})
WORK_DIR="${TOOLS_DIR}/.."

cd "${WORK_DIR}"

version_with_v=$(git describe --tags --abbrev=0)
VERSION=$(echo ${version_with_v} | cut -f2 -dv)
sed -i "s/#define CRT_VERSION .*/#define CRT_VERSION \"$VERSION\"/g" ext/crt.c

export VERSION="${VERSION}"
