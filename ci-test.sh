#!/usr/bin/env bash

set -ex

PHP_VERSION=$(php --version | head -1 | cut -f 2 -d' ' | cut -f1 -d.)

make test-extension

if [[ $PHP_VERSION -ge 7 ]]; then
  make test-ffi
fi