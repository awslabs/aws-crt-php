
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

#if ZEND_EXTENSION_API_NO < ZEND_EXTENSION_API_NO_5_6_X
#    error "PHP >= 5.6 is required"
#endif

ZEND_BEGIN_MODULE_GLOBALS(awscrt)
long log_level;
ZEND_END_MODULE_GLOBALS(awscrt)

ZEND_EXTERN_MODULE_GLOBALS(awscrt)

#define AWSCRT_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(awscrt, v)

/* PHP 7 removed the string duplicate parameter */
#if ZEND_EXTENSION_API_NO < ZEND_EXTENSION_API_NO_7_0_X
#    define AWS_RETURN_STRING(s) RETURN_STRING(s, 1)
#else
#    define AWS_RETURN_STRING(s) RETURN_STRING(s)
#endif

#endif /* PHP_AWS_CRT_H */
