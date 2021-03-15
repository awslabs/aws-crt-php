
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include "php_aws_crt.h"

#include "api.h"

#include "awscrt_arginfo.h"

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
PHP_FUNCTION(aws_crt_last_error) {
    RETURN_LONG(aws_crt_last_error());
}

/* aws_crt_error_str(int error_code) */
PHP_FUNCTION(aws_crt_error_str) {
    zend_ulong error_code = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &error_code) == FAILURE) {
        RETURN_NULL();
    }

    AWS_RETURN_STRING(aws_crt_error_str(error_code));
}

/* aws_crt_error_name(int error_code) */
PHP_FUNCTION(aws_crt_error_name) {
    zend_ulong error_code = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &error_code) == FAILURE) {
        RETURN_NULL();
    }

    AWS_RETURN_STRING(aws_crt_error_name(error_code));
}

/* aws_crt_error_debug_str(int error_code) */
PHP_FUNCTION(aws_crt_error_debug_str) {
    zend_ulong error_code = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &error_code) == FAILURE) {
        RETURN_NULL();
    }

    AWS_RETURN_STRING(aws_crt_error_debug_str(error_code));
}

PHP_FUNCTION(aws_crt_event_loop_group_options_new) {
    aws_crt_event_loop_group_options *options = aws_crt_event_loop_group_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_event_loop_group_options_release) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        return;
    }

    aws_crt_event_loop_group_options *options = (void *)php_options;
    aws_crt_event_loop_group_options_release(options);
}

PHP_FUNCTION(aws_crt_event_loop_group_options_set_max_threads) {
    zend_ulong php_options = 0;
    zend_ulong num_threads = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &php_options, &num_threads) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_event_loop_group_options *options = (void *)php_options;
    aws_crt_event_loop_group_options_set_max_threads(options, num_threads);
}

PHP_FUNCTION(aws_crt_event_loop_group_new) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_event_loop_group_options *options = (void *)php_options;
    struct aws_event_loop_group *elg = aws_crt_event_loop_group_new(options);
    RETURN_LONG((zend_ulong)elg);
}

PHP_FUNCTION(aws_crt_event_loop_group_release) {
    zend_ulong php_elg = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_elg) == FAILURE) {
        return;
    }

    struct aws_event_loop_group *elg = (void *)php_elg;
    aws_crt_event_loop_group_release(elg);
}

PHP_FUNCTION(aws_crt_credentials_options_new) {
    aws_crt_credentials_options *options = aws_crt_credentials_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_credentials_options_release) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_release(options);
}

PHP_FUNCTION(aws_crt_credentials_options_set_access_key_id) {
    zend_ulong php_options = 0;
    zend_string *php_access_key_id;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lS", &php_options, &php_access_key_id) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    const char *access_key_id = ZSTR_VAL(php_access_key_id);
    size_t access_key_id_len = ZSTR_LEN(php_access_key_id);
    aws_crt_credentials_options_set_access_key_id(options, (uint8_t *)access_key_id, access_key_id_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_secret_access_key) {
    zend_ulong php_options = 0;
    zend_string *php_secret_access_key;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lS", &php_options, &php_secret_access_key) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    const char *secret_access_key = ZSTR_VAL(php_secret_access_key);
    size_t secret_access_key_len = ZSTR_LEN(php_secret_access_key);
    aws_crt_credentials_options_set_secret_access_key(options, (uint8_t *)secret_access_key, secret_access_key_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_session_token) {
    zend_ulong php_options = 0;
    zend_string *php_session_token;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lS", &php_options, &php_session_token) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    const char *session_token = ZSTR_VAL(php_session_token);
    size_t session_token_len = ZSTR_LEN(php_session_token);
    aws_crt_credentials_options_set_session_token(options, (uint8_t *)session_token, session_token_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_expiration_timepoint_seconds) {
    zend_ulong php_options = 0;
    zend_ulong expiration_timepoint_seconds = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &php_options, &expiration_timepoint_seconds) ==
        FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_expiration_timepoint_seconds(options, expiration_timepoint_seconds);
}

PHP_FUNCTION(aws_crt_credentials_new) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials *credentials = aws_crt_credentials_new(options);
    RETURN_LONG((zend_ulong)credentials);
}

PHP_FUNCTION(aws_crt_credentials_release) {
    zend_ulong php_credentials = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_credentials) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials *credentials = (void *)php_credentials;
    aws_crt_credentials_release(credentials);
}

PHP_FUNCTION(aws_crt_credentials_provider_release) {
    zend_ulong php_creds_provider = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_creds_provider) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider *provider = (void *)php_creds_provider;
    aws_crt_credentials_provider_release(provider);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_new) {
    aws_crt_credentials_provider_static_options *options = aws_crt_credentials_provider_static_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_release) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider_static_options_release(options);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_access_key_id) {
    zend_ulong php_options = 0;
    zend_string *php_access_key_id;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lS", &php_options, &php_access_key_id) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    const char *access_key_id = ZSTR_VAL(php_access_key_id);
    size_t access_key_id_len = ZSTR_LEN(php_access_key_id);
    aws_crt_credentials_provider_static_options_set_access_key_id(options, (uint8_t *)access_key_id, access_key_id_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_secret_access_key) {
    zend_ulong php_options = 0;
    zend_string *php_secret_access_key;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lS", &php_options, &php_secret_access_key) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    const char *secret_access_key = ZSTR_VAL(php_secret_access_key);
    size_t secret_access_key_len = ZSTR_LEN(php_secret_access_key);
    aws_crt_credentials_provider_static_options_set_secret_access_key(
        options, (uint8_t *)secret_access_key, secret_access_key_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_session_token) {
    zend_ulong php_options = 0;
    zend_string *php_session_token;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lS", &php_options, &php_session_token) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    const char *session_token = ZSTR_VAL(php_session_token);
    size_t session_token_len = ZSTR_LEN(php_session_token);
    aws_crt_credentials_provider_static_options_set_session_token(options, (uint8_t *)session_token, session_token_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_new) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider *provider = aws_crt_credentials_provider_static_new(options);
    RETURN_LONG((zend_ulong)provider);
}

zend_module_entry awscrt_module_entry = {
    STANDARD_MODULE_HEADER,
    "awscrt",
    ext_functions, /* functions */
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
    STANDARD_MODULE_PROPERTIES_EX,
};

#ifdef COMPILE_DL_AWSCRT
ZEND_GET_MODULE(awscrt)
#endif
