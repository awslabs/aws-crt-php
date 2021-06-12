#!/usr/bin/env bash

set -ex

PHP_VERSION=$(php --version | head -1 | cut -f 2 -d' ')

if [[ $PHP_VERSION -ge 7 ]]; then
  make test-ffi
  make test-extension
else
  make test-extension
fi