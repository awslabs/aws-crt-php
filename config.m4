dnl
dnl * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
dnl * SPDX-License-Identifier: Apache-2.0.
dnl

PHP_ARG_WITH(awscrt)

if test "$PHP_AWSCRT" != "no"; then
    # AC_MSG_CHECKING([for libcrypto])
    # for search_path in "$AWS_LIBCRYTO_INSTALL" "$PHP_AWSCRT/build/deps/openssl" /opt/openssl /usr/local /usr; do
    #     if test -f "$search_path/include/openssl/crypto.h"; then
    #         LIBCRYPTO_PATH=$search_path
    #         break
    #     fi
    # done
    # if test -z "$LIBCRYPTO_PATH"; then
    #     AC_MSG_ERROR([not found])
    # fi

    # AC_MSG_RESULT([found at $LIBCRYPTO_PATH])
    # PHP_ADD_INCLUDE($LIBCRYPTO_PATH/include)
    #PHP_ADD_LIBRARY_WITH_PATH(:libcrypto.a, [build/install/lib], AWSCRT_SHARED_LIBADD)

    dnl awscrt
    cwd=`pwd`
    CRT_LIBPATHS="-L${cwd}/build/install/lib64 -L${cwd}/build/install/lib"
    CRT_LIBS="-laws-c-auth -laws-c-http -laws-c-cal -laws-c-io -laws-c-compression -laws-c-common -ls2n -l:libcrypto.a"
    # PHP_ADD_LIBPATH([build/install/lib64], AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBPATH([build/install/lib], AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(aws-c-common,, AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(s2n,, AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(aws-c-io,, AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(aws-c-cal,, AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(aws-c-compression,, AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(aws-c-http,, AWSCRT_SHARED_LIBADD)
    # PHP_ADD_LIBRARY(aws-c-auth,, AWSCRT_SHARED_LIBADD)
    PHP_EVAL_LIBLINE([$CRT_LIBPATHS $CRT_LIBS], AWSCRT_SHARED_LIBADD)
    PHP_SUBST(AWSCRT_SHARED_LIBADD)

    AWSCRT_SOURCES=src/*.c
    PHP_NEW_EXTENSION(awscrt, $AWSCRT_SOURCES, $ext_shared)
fi

PHP_ADD_MAKEFILE_FRAGMENT
