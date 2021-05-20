dnl
dnl * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
dnl * SPDX-License-Identifier: Apache-2.0.
dnl

PHP_ARG_WITH(awscrt)

if test "$PHP_AWSCRT" != "no"; then
    # force lib paths to be absolute, or PHP will mangle them
    cwd=`pwd`
    # Enable s2n and libcrypto for non-darwin UNIX
    if uname -a | grep -i darwin > /dev/null 2>&1; then
        platform_tls_libs=""
    else
        platform_tls_libs="-ls2n -l:libcrypto.a"
    fi
    CRT_LIBPATHS="-L${cwd}/build/install/lib -L${cwd}/build/install/lib64"
    CRT_LIBS="-laws-crt-ffi -laws-c-auth -laws-c-http -laws-c-io -laws-c-cal -laws-c-compression -laws-c-common ${platform_tls_libs}"
    PHP_ADD_INCLUDE(${cwd}/build/install/include)
    PHP_EVAL_LIBLINE([$CRT_LIBPATHS $CRT_LIBS], AWSCRT_SHARED_LIBADD)

    # Shoves the linker line into the Makefile
    PHP_SUBST(AWSCRT_SHARED_LIBADD)

    # Sources for the PHP extension itself
    AWSCRT_SOURCES=ext/credentials.c ext/crt.c ext/event_loop.c ext/http.c ext/signing.c ext/stream.c
    PHP_NEW_EXTENSION(awscrt, $AWSCRT_SOURCES, $ext_shared)
fi

PHP_ADD_MAKEFILE_FRAGMENT
