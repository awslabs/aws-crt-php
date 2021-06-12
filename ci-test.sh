#!/usr/bin/env bash

set -ex

HAS_FFI=$(php -m | grep FFI | wc -l)

make test-extension

if [[ $HAS_FFI -gt 0 ]]; then
  make test-ffi
fi