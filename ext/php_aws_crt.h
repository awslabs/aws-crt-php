
#ifndef PHP_AWS_CRT_H
#define PHP_AWS_CRT_H

/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#ifdef HAVE_CONFIG_H
#    include "config.h"
#endif

#include "php.h"

#include "Zend/zend_extensions.h" /* for ZEND_EXTENSION_API_NO */

#if ZEND_EXTENSION_API_NO < 220131226
#    error "PHP >= 5.6 is required"
#endif

#define AWS_PHP_AT_LEAST_7 (ZEND_EXTENSION_API_NO >= 320151012)

ZEND_BEGIN_MODULE_GLOBALS(awscrt)
long log_level;
ZEND_END_MODULE_GLOBALS(awscrt)

ZEND_EXTERN_MODULE_GLOBALS(awscrt)

#define AWSCRT_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(awscrt, v)


#if AWS_PHP_AT_LEAST_7
/* PHP 7 removed the string duplicate parameter */
#    define AWS_RETURN_STRING(s) RETURN_STRING(s)
#    define AWS_RETURN_STRINGL(s, l) RETURN_STRINGL(s, l)
/* PHP 7 takes a zval*, PHP5 takes a zval** */
#    define AWS_PHP_STREAM_FROM_ZVAL(s, z) php_stream_from_zval(s, z)
#else
#    define AWS_RETURN_STRING(s) RETURN_STRING(s, 1)
#    define AWS_RETURN_STRINGL(s, l) RETURN_STRINGL(s, l, 1)
#    define AWS_PHP_STREAM_FROM_ZVAL(s, z) php_stream_from_zval(s, &z)

/* definitions for ZEND API macros taken from PHP7 and backported to 5.6 */
#    define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null)       \
        static const zend_arg_info name[] = {{NULL, 0, NULL, required_num_args, return_reference, 0, 0},

/* PHP5 doesn't really handle type hints well, so elide them */
#    undef ZEND_ARG_TYPE_INFO
#    define ZEND_ARG_TYPE_INFO(pass_by_ref, name, type_hint, allow_null)                                               \
        {#name, sizeof(#name) - 1, NULL, 0, 0, pass_by_ref, allow_null, 0},
#endif

#endif /* PHP_AWS_CRT_H */
