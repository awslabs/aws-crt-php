
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include "php_aws_crt.h"

#include "api.h"

#include "awscrt_arginfo.h"

/* Helpful references for this file:
 * zend_parse_parameters and friends -
 * https://git.php.net/?p=php-src.git;a=blob;f=docs/parameter-parsing-api.md;h=c962fc6ee58cc756aaac9e65759b7d5ea5c18fc4;hb=HEAD
 * https://git.php.net/?p=php-src.git;a=blob;f=docs/self-contained-extensions.md;h=47f4c636baca8ca195118e2cc234ac7fd2842c1b;hb=HEAD
 * Examples:
 * Curl extension: https://github.com/php/php-src/blob/PHP-5.6/ext/curl/interface.c
 * libuv extension: https://github.com/amphp/ext-uv/blob/master/php_uv.c
 */

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
    aws_crt_event_loop_group *elg = aws_crt_event_loop_group_new(options);
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

PHP_FUNCTION(aws_crt_input_stream_options_new) {
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_input_stream_options *options = aws_crt_input_stream_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_input_stream_options_release) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        return;
    }

    aws_crt_input_stream_options *options = (void *)php_options;
    aws_crt_input_stream_options_release(options);
}

/* PHP streams info:
 * https://git.php.net/?p=php-src.git;a=blob;f=docs/streams.md;h=0ec3846d68bf70067297d8a6c691d2591c49b48a;hb=HEAD
 * https://github.com/php/php-src/blob/PHP-5.6.0/main/php_streams.h
 */

PHP_FUNCTION(aws_crt_input_stream_options_set_user_data) {
    zend_ulong php_options = 0;
    zval *user_data = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &php_options, &user_data) == FAILURE) {
        return;
    }

    aws_crt_input_stream_options *options = (void *)php_options;
    php_stream *stream = NULL;
    php_stream_from_zval(stream, user_data);
    aws_crt_input_stream_options_set_user_data(options, stream);
}

static int s_php_stream_seek(void *user_data, int64_t offset, aws_crt_stream_seek_basis basis) {
    php_stream *stream = user_data;
    return php_stream_seek(stream, offset, basis);
}

static int s_php_stream_read(void *user_data, uint8_t* dest, size_t dest_length) {
    php_stream *stream = user_data;
    return php_stream_read(stream, dest, dest_length) != 0;
}

static int s_php_stream_get_status(void *user_data, aws_crt_stream_status *out_status) {
    php_stream *stream = user_data;
    out_status->is_valid = stream != NULL;
    out_status->is_end_of_stream = php_stream_eof(stream);
    return 0;
}

static int s_php_stream_get_length(void *user_data, int64_t *out_length) {
    php_stream *stream = user_data;
    *out_length = php_stream_tell(stream);
    return 0;
}

static void s_php_stream_destroy(void *user_data) {
    php_stream *stream = user_data;
    php_stream_close(stream);
}

PHP_FUNCTION(aws_crt_input_stream_new) {
    zend_ulong php_options = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_options) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_input_stream_options *options = (void *)php_options;
    aws_crt_input_stream_options_set_seek(options, s_php_stream_seek);
    aws_crt_input_stream_options_set_read(options, s_php_stream_read);
    aws_crt_input_stream_options_set_get_status(options, s_php_stream_get_status);
    aws_crt_input_stream_options_set_get_length(options, s_php_stream_get_length);
    aws_crt_input_stream_options_set_destroy(options, s_php_stream_destroy);
    aws_crt_input_stream *stream = aws_crt_input_stream_new(options);
    RETURN_LONG((zend_ulong)stream);
}

PHP_FUNCTION(aws_crt_input_stream_release) {
    zend_ulong php_stream = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &php_stream) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_input_stream *stream = (void *)php_stream;
    aws_crt_input_stream_release(stream);
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
    const char *access_key_id = NULL;
    size_t access_key_id_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &php_options, &access_key_id, &access_key_id_len) ==
        FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_access_key_id(options, (uint8_t *)access_key_id, access_key_id_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_secret_access_key) {
    zend_ulong php_options = 0;
    const char *secret_access_key = NULL;
    size_t secret_access_key_len = 0;

    if (zend_parse_parameters(
            ZEND_NUM_ARGS() TSRMLS_CC, "ls", &php_options, &secret_access_key, &secret_access_key_len) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_secret_access_key(options, (uint8_t *)secret_access_key, secret_access_key_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_session_token) {
    zend_ulong php_options = 0;
    const char *session_token = NULL;
    size_t session_token_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &php_options, &session_token, &session_token_len) ==
        FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
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
    const char *access_key_id = NULL;
    size_t access_key_id_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &php_options, &access_key_id, &access_key_id_len) ==
        FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider_static_options_set_access_key_id(options, (uint8_t *)access_key_id, access_key_id_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_secret_access_key) {
    zend_ulong php_options = 0;
    const char *secret_access_key = NULL;
    size_t secret_access_key_len = 0;

    if (zend_parse_parameters(
            ZEND_NUM_ARGS() TSRMLS_CC, "ls", &php_options, &secret_access_key, &secret_access_key_len) == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider_static_options_set_secret_access_key(
        options, (uint8_t *)secret_access_key, secret_access_key_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_session_token) {
    zend_ulong php_options = 0;
    const char *session_token = NULL;
    size_t session_token_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &php_options, &session_token, &session_token_len) ==
        FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
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

,   NULL, /* RINIT */
NULL, /* RSHUTDOWN NULL, /* MINFO */
     NO_VE                        R SION_YET,
    PHP_M                       O                                        DULE_GLOBALS(awscrt),
    PHP_G        I                                                       NIT(awscrt),
    NULL, /* GSHUTD NULL, /* RPOSTSHUT(awscrt), PHP_GINITDOWN */
, NULL  /* GSHUTDOWN */
    NULL,                                                                /* RPOSTSHUTDOWN */   STANDARD_MODULE_PROPERTIES_EX,
};

#ifdef COMPILE_DL_AWSCRT
ZEND_GET_MODULE(awscrt)
#endif
ZEND_GET_MODULE(awscrt)
#endif
