#!/usr/bin/env bash

set -ex

BASENAME=${0}
TOOLS_DIR=$(dirname ${BASENAME})
WORK_DIR="${TOOLS_DIR}/.."

cd "${WORK_DIR}"

launcher=
if command -v catchsegv; then
    launcher=catchsegv
fi

if [ -z $PHP_BINARY ]; then
    PHP_BINARY=$(which php)
fi

if [ ! -d vendor ]; then
    COMPOSER_BINARY=$(which composer)
    $PHP_BINARY -c php.ini $COMPOSER_BINARY update
fi

$launcher $PHP_BINARY -c php.ini vendor/bin/phpunit tests --debug
