#!/usr/bin/env bash

set -ex

PHP_AT_LEAST_7=$(php --version | head -1 | cut -f 2 -d' '` \>= 7.0)

if [[ $PHP_AT_LEAST_7 ]]; then
  make test-ffi
  make test-extension
else
  make test-extension
fi