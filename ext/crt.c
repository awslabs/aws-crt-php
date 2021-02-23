
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include "php_aws_crt.h"

#include "api.h"

ZEND_DECLARE_MODULE_GLOBALS(awscrt);

PHP_INI_BEGIN()
STD_PHP_INI_ENTRY(
    "awscrt.log_level",
    "",
    PHP_INI_ALL,
    OnUpdateLongGEZero,
    log_level,
    zend_awscrt_globals,
    awscrt_globals)
PHP_INI_END()

static PHP_MINIT_FUNCTION(awscrt) {
    REGISTER_INI_ENTRIES();

    aws_crt_init();
    return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(awscrt) {
    UNREGISTER_INI_ENTRIES();
    aws_crt_clean_up();
    return SUCCESS;
}

static PHP_GINIT_FUNCTION(awscrt) {
#if defined(COMPILE_DL_ASTKIT) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    awscrt_globals->log_level = 0;
}

/* aws_crt_last_error() */
ZEND_BEGIN_ARG_INFO(aws_crt_last_error_arginfo, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(aws_crt_last_error) {
    RETURN_LONG(aws_crt_last_error());
}

/* aws_crt_error_str(int) */
ZEND_BEGIN_ARG_INFO(aws_crt_error_str_arginfo, 1)
ZEND_ARG_TYPE_INFO(0, error_code, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(aws_crt_error_str) {
    zend_long error_code = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(error_code)
    ZEND_PARSE_PARAMETERS_END();

    AWS_RETURN_STRING(aws_crt_error_str(error_code));
}

/* aws_crt_error_name(int) */
ZEND_BEGIN_ARG_INFO(aws_crt_error_name_arginfo, 1)
ZEND_ARG_TYPE_INFO(0, error_code, IS_LONG, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(aws_crt_error_name) {
    zend_long error_code = 0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(error_code);
    ZEND_PARSE_PARAMETERS_END();

    AWS_RETURN_STRING(aws_crt_error_name(error_code));
}

#define AWS_PHP_FE(fun) PHP_FE(fun, fun##_arginfo)

/* clang-format off */
const zend_function_entry awscrt_functions[] = {
    AWS_PHP_FE(aws_crt_last_error)
    AWS_PHP_FE(aws_crt_error_str)
    AWS_PHP_FE(aws_crt_error_name)
    PHP_FE_END
};

zend_module_entry awscrt_module_entry = {
    STANDARD_MODULE_HEADER,
    "awscrt",
    awscrt_functions, /* functions */
    PHP_MINIT(awscrt),
    PHP_MSHUTDOWN(awscrt),
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
    NO_VERSION_YET,
    PHP_MODULE_GLOBALS(awscrt),
    PHP_GINIT(awscrt),
    NULL, /* GSHUTDOWN */
    NULL, /* RPOSTSHUTDOWN */
    STANDARD_MODULE_PROPERTIES_EX};

/* clang-format on */

#ifdef COMPILE_DL_AWSCRT
ZEND_GET_MODULE(awscrt)
#endif
