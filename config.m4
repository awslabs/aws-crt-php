dnl
dnl * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
dnl * SPDX-License-Identifier: Apache-2.0.
dnl

PHP_ARG_WITH(awscrt)

if test "$PHP_AWSCRT" != "no"; then
    # force lib paths to be absolute, or PHP will mangle them
    cwd=`pwd`
    CRT_LIBPATHS="-L${cwd}/build/install/lib64 -L${cwd}/build/install/lib"
    CRT_LIBS="-laws-c-auth -laws-c-http -laws-c-cal -laws-c-io -laws-c-compression -laws-c-common -ls2n -l:libcrypto.a"
    PHP_ADD_INCLUDE(${cwd}/build/install/include)
    PHP_EVAL_LIBLINE([$CRT_LIBPATHS $CRT_LIBS], AWSCRT_SHARED_LIBADD)

    # Shoves the linker line into the Makefile
    PHP_SUBST(AWSCRT_SHARED_LIBADD)

    # Sources for the PHP extension itself
    AWSCRT_SOURCES=ext/*.c
    PHP_NEW_EXTENSION(awscrt, $AWSCRT_SOURCES, $ext_shared)
fi

PHP_ADD_MAKEFILE_FRAGMENT
