dnl
dnl * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
dnl * SPDX-License-Identifier: Apache-2.0.
dnl

PHP_ARG_WITH(awscrt)

if test "$PHP_AWSCRT" != "no"; then
    AC_MSG_CHECKING([for libcrypto])
    for search_path in "$AWS_LIBCRYTO_INSTALL" "$PHP_AWSCRT/build/deps/openssl" /opt/openssl /usr/local /usr; do
        if test -f "$search_path/include/openssl/crypto.h"; then
            LIBCRYPTO_PATH=$search_path
            break
        fi
    done
    if test -z "$LIBCRYPTO_PATH"; then
        AC_MSG_ERROR([not found])
    fi

    AC_MSG_RESULT([found at $LIBCRYPTO_PATH])

    PHP_ADD_INCLUDE($LIBCRYPTO_PATH/include)
    dnl PHP_ADD_LIBPATH($LIBCRYPTO_PATH/lib)
    PHP_ADD_LIBRARY_WITH_PATH(:libcrypto.a, $LIBCRYPTO_PATH/lib, AWSCRT_SHARED_LIBADD)

    AWSCRT_SOURCES=src/*.c

    PHP_NEW_EXTENSION(awscrt, $AWSCRT_SOURCES, $ext_shared)
    PHP_SUBST(AWSCRT_SHARED_LIBADD)
fi
