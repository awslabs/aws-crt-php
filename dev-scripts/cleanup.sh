#!/usr/bin/env bash

BASENAME=${0}
TOOLS_DIR=$(dirname ${BASENAME})
WORK_DIR="${TOOLS_DIR}/.."

cd "${WORK_DIR}"

find . -name \*.tgz -a |xargs rm -rf

## get rid of anything that phpize, configure and make as well
rm -rf .deps \
.libs \
Makefile \
Makefile.fragments \
Makefile.global \
Makefile.objects \
acinclude.m4 \
aclocal.m4 \
autom4te.cache \
build \
config.guess \
config.h \
config.h.in* \
config.log \
config.nice \
config.status \
config.sub \
configure \
configure.in \
configure.ac \
include \
install-sh \
libtool \
ltmain.sh \
missing \
mkinstalldirs \
modules \
run-tests.php \
awscrt.la \
vendor \
composer.lock \
ext/awscrt.stub.php \

find . -name \*.lo -o -name \*.o | xargs rm -f
find . -name \*.la -o -name \*.a | xargs rm -f
find . -name \*.so | xargs rm -f
find . -name .libs -a -type d|xargs rm -rf
