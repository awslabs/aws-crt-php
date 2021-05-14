
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

static size_t s_count_args(const char *arg_types) {
    size_t num_args = 0;
    const char *arg = &arg_types[0];
    while (*arg != '\0') {
        switch (*arg++) {
            /* multi-arg types */
            case 'p':
            case 's':
                num_args += 2;
                break;
            default:
                num_args += 1;
                break;
        }
    }
    return num_args;
}

#ifndef AWS_COMMON_MACROS_H
#define GLUE(x, y) x y

#define RETURN_ARG_COUNT(_1_, _2_, _3_, _4_, _5_, count, ...) count
#define EXPAND_ARGS(args) RETURN_ARG_COUNT args
#define COUNT_ARGS_MAX5(...) EXPAND_ARGS((__VA_ARGS__, 5, 4, 3, 2, 1, 0))

#define OVERLOAD_MACRO2(name, count) name##count
#define OVERLOAD_MACRO1(name, count) OVERLOAD_MACRO2(name, count)
#define OVERLOAD_MACRO(name, count) OVERLOAD_MACRO1(name, count)

#define CALL_OVERLOAD(name, ...) GLUE(OVERLOAD_MACRO(name, COUNT_ARGS_MAX5(__VA_ARGS__)), (__VA_ARGS__))

#define VARIABLE_LENGTH_ARRAY(type, name, length) type *name = alloca(sizeof(type) * (length))
#endif

/*
 * Exception throwing mechanism, will never return
 */
#define _AWS_PHP_THROW_EXCEPTION5(format, ...) zend_error_noreturn(E_ERROR, format, __VA_ARGS__)
#define _AWS_PHP_THROW_EXCEPTION4(format, ...) zend_error_noreturn(E_ERROR, format, __VA_ARGS__)
#define _AWS_PHP_THROW_EXCEPTION3(format, ...) zend_error_noreturn(E_ERROR, format, __VA_ARGS__)
#define _AWS_PHP_THROW_EXCEPTION2(format, ...) zend_error_noreturn(E_ERROR, format, __VA_ARGS__)
#define _AWS_PHP_THROW_EXCEPTION1(format) zend_error_noreturn(E_ERROR, format)

#define aws_php_throw_exception(...) CALL_OVERLOAD(_AWS_PHP_THROW_EXCEPTION, __VA_ARGS__);

/* throws an exception resulting from argument parsing, notes the current function name in the exception */
#define aws_php_argparse_fail() do { \
    aws_php_throw_exception("Failed to parse arguments to %s", __func__); \
} while (0)

/* calls zend_parse_parameters() with the arguments and throws an exception if parsing fails */
#define aws_php_parse_parameters(type_spec, ...) do { \
    if (zend_parse_parameters(ZEND_NUM_ARGS(), type_spec, __VA_ARGS__) == FAILURE) { \
        aws_php_argparse_fail(); \
    } \
} while (0)

/* calls zend_parse_parameters_none() and throws an exception if parsing fails */
#define aws_php_parse_parameters_none() do { \
    if (zend_parse_parameters_none() == FAILURE) { \
        aws_php_argparse_fail(); \
    } \
} while (0)

/*
 * generic dispatch mechanism to call a callback provided as a zval with arguments
 * that are converted to zvals based on the arg_types format string
 */
static zval *aws_php_invoke_callback(zval *callback, const char *arg_types, ...) {
    if (!zend_is_callable(callback, IS_CALLABLE_CHECK_SYNTAX_ONLY, NULL) &&
        !zend_make_callable(callback, NULL)) {
        aws_php_throw_exception("callback provided is not a callable and is not convertible to a callable");
    }

    char *error = NULL;
    zend_fcall_info fci = {0};
    zend_fcall_info_cache fcc = {0};
    if (zend_fcall_info_init(callback, IS_CALLABLE_CHECK_SYNTAX_ONLY, &fci, &fcc, NULL, &error) == FAILURE) {
        aws_php_throw_exception("Unable to initialize callback from callable via zend_fcall_info_init: %s", error);
    }

    /* Allocate the stack frame of zval arguments and fill them in */
    const size_t num_args = s_count_args(arg_types);
    zval *stack = alloca(sizeof(zval) * num_args);
    zval *retval = NULL;
    int arg_idx = 0;
    va_list va;
    va_start(va, arg_types);
    while (arg_idx < num_args) {
        const char arg_type = arg_types[arg_idx];
        switch (arg_type) {
            /* zval types */
            case 'a':
            case 'A':
            case 'n':
            case 'o':
            case 'r':
            case 'z': {
                zval *zval_val = va_arg(va, zval*);
                ZVAL_ZVAL(&stack[arg_idx], zval_val, 0, 0);
                break;
            }
            /* buffers/strings (char *, size_t) */
            case 'p':
            case 's': {
                const char *buf = va_arg(va, const char*);
                const size_t len = va_arg(va, size_t);
                ZVAL_STRINGL(&stack[arg_idx], buf, len);
                break;
            }
            /* other primitives */
            case 'b': {
                zend_bool bool_val = va_arg(va, int);
                ZVAL_BOOL(&stack[arg_idx], bool_val);
                break;
            }
            case 'd': {
                double double_val = va_arg(va, double);
                ZVAL_DOUBLE(&stack[arg_idx], double_val);
                break;
            }
            case 'l': {
                zend_ulong long_val = va_arg(va, zend_ulong);
                ZVAL_LONG(&stack[arg_idx], long_val);
                break;
            }
            /* strings (zend_string), not supported in PHP 5.6, therefore not supported */
            case 'P':
            case 'S':
            /* unsupported */
            case 'C':
            case 'f':
            case 'h':
            case 'H':
            case 'O':
                aws_php_throw_exception("Unsupported argument type to aws_php_invoke_callback: %c", arg_type);
            default:
                aws_php_throw_exception("Unsupported argument type to aws_php_invoke_callback: %c", arg_type);
        }
        ++arg_idx;
    }
    va_end(va);

    /* set up the stack for the call */
    zend_fcall_info_argp(&fci, num_args, stack);

    /* PHP5 requires us to have a retval on the stack that zend fills out */
#if !defined(AWS_PHP_AT_LEAST_7)
    fci.retval_ptr_ptr = &retval;
#endif

    if (zend_call_function(&fci, &fcc) == FAILURE) {
        aws_php_throw_exception("zend_call_function failed in aws_php_invoke_callback");
    }

    /* PHP7+ allocates its own retval, so we need to copy it out */
#if defined(AWS_PHP_AT_LEAST_7)
    retval = fci.retval;
#endif

    /* Clean up arguments. Note that some arguments may have been mutated due to
     * type coercion */
    for (int arg_idx = 0; arg_idx < num_args; ++arg_idx) {
        zval_ptr_dtor(&stack[arg_idx]);
    }

    return retval;
}


/* aws_crt_last_error() */
PHP_FUNCTION(aws_crt_last_error) {
    RETURN_LONG(aws_crt_last_error());
}

/* aws_crt_error_str(int error_code) */
PHP_FUNCTION(aws_crt_error_str) {
    zend_ulong error_code = 0;
    aws_php_parse_parameters("l", &error_code);

    AWS_RETURN_STRING(aws_crt_error_str(error_code));
}

/* aws_crt_error_name(int error_code) */
PHP_FUNCTION(aws_crt_error_name) {
    zend_ulong error_code = 0;
    aws_php_parse_parameters("l", &error_code);

    AWS_RETURN_STRING(aws_crt_error_name(error_code));
}

/* aws_crt_error_debug_str(int error_code) */
PHP_FUNCTION(aws_crt_error_debug_str) {
    zend_ulong error_code = 0;
    aws_php_parse_parameters("l", &error_code);

    AWS_RETURN_STRING(aws_crt_error_debug_str(error_code));
}

PHP_FUNCTION(aws_crt_event_loop_group_options_new) {
    aws_php_parse_parameters_none();
    aws_crt_event_loop_group_options *options = aws_crt_event_loop_group_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_event_loop_group_options_release) {
    zend_ulong php_options = 0;
    aws_php_parse_parameters("l", &php_options);

    aws_crt_event_loop_group_options *options = (void *)php_options;
    aws_crt_event_loop_group_options_release(options);
}

PHP_FUNCTION(aws_crt_event_loop_group_options_set_max_threads) {
    zend_ulong php_options = 0;
    zend_ulong num_threads = 0;
    aws_php_parse_parameters("ll", &php_options, &num_threads);

    aws_crt_event_loop_group_options *options = (void *)php_options;
    aws_crt_event_loop_group_options_set_max_threads(options, num_threads);
}

PHP_FUNCTION(aws_crt_event_loop_group_new) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

    aws_crt_event_loop_group_options *options = (void *)php_options;
    aws_crt_event_loop_group *elg = aws_crt_event_loop_group_new(options);
    RETURN_LONG((zend_ulong)elg);
}

PHP_FUNCTION(aws_crt_event_loop_group_release) {
    zend_ulong php_elg = 0;

    aws_php_parse_parameters("l", &php_elg);

    struct aws_event_loop_group *elg = (void *)php_elg;
    aws_crt_event_loop_group_release(elg);
}

PHP_FUNCTION(aws_crt_input_stream_options_new) {
    if (zend_parse_parameters_none() == FAILURE) {
        aws_php_argparse_fail();
    }

    aws_crt_input_stream_options *options = aws_crt_input_stream_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_input_stream_options_release) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

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

    aws_php_parse_parameters("lz", &php_options, &user_data);

    aws_crt_input_stream_options *options = (void *)php_options;
    php_stream *stream = NULL;
    AWS_PHP_STREAM_FROM_ZVAL(stream, user_data);
    aws_crt_input_stream_options_set_user_data(options, stream);
}

static int s_php_stream_seek(void *user_data, int64_t offset, aws_crt_input_stream_seek_basis basis) {
    php_stream *stream = user_data;
    return php_stream_seek(stream, offset, basis);
}

static int s_php_stream_read(void *user_data, uint8_t *dest, size_t dest_length) {
    php_stream *stream = user_data;
    return php_stream_read(stream, (char *)dest, dest_length) != 0;
}

static int s_php_stream_get_length(void *user_data, int64_t *out_length) {
    php_stream *stream = user_data;
    size_t pos = php_stream_tell(stream);
    php_stream_seek(stream, 0, SEEK_END);
    *out_length = php_stream_tell(stream);
    php_stream_seek(stream, pos, SEEK_SET);
    return 0;
}

static int s_php_stream_get_status(void *user_data, aws_crt_input_stream_status *out_status) {
    php_stream *stream = user_data;
    out_status->is_valid = stream != NULL;
    /* We would like to use php_stream_eof here, but certain streams (notably php://memory)
     * are not actually capable of EOF, so we get to do it the hard way */
    int64_t length = 0;
    int64_t pos = 0;
    s_php_stream_get_length(stream, &length);
    pos = php_stream_tell(stream);
    out_status->is_end_of_stream = pos == length;
    return 0;
}

static void s_php_stream_destroy(void *user_data) {
    (void)user_data;
    /* no op, stream will be freed by PHP refcount dropping from InputStream::stream */
}

PHP_FUNCTION(aws_crt_input_stream_new) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

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

    aws_php_parse_parameters("l", &php_stream);

    aws_crt_input_stream *stream = (void *)php_stream;
    aws_crt_input_stream_release(stream);
}

PHP_FUNCTION(aws_crt_input_stream_seek) {
    zend_ulong php_stream = 0;
    zend_ulong offset = 0;
    zend_ulong basis = 0;

    aws_php_parse_parameters("lll", &php_stream, &offset, &basis);

    aws_crt_input_stream *stream = (void *)php_stream;
    RETURN_LONG(aws_crt_input_stream_seek(stream, offset, basis));
}

PHP_FUNCTION(aws_crt_input_stream_read) {
    zend_ulong php_stream = 0;
    zend_ulong length = 0;

    aws_php_parse_parameters("ll", &php_stream, &length);

    aws_crt_input_stream *stream = (void *)php_stream;
    uint8_t *buf = emalloc(length);
    int ret = aws_crt_input_stream_read(stream, buf, length);
    AWS_RETURN_STRINGL((const char *)buf, length);
    efree(buf);
}

PHP_FUNCTION(aws_crt_input_stream_eof) {
    zend_ulong php_stream = 0;

    aws_php_parse_parameters("l", &php_stream);

    aws_crt_input_stream *stream = (void *)php_stream;
    aws_crt_input_stream_status status = {0};
    aws_crt_input_stream_get_status(stream, &status);
    RETURN_BOOL(status.is_end_of_stream);
}

PHP_FUNCTION(aws_crt_input_stream_get_length) {
    zend_ulong php_stream = 0;

    aws_php_parse_parameters("l", &php_stream);

    aws_crt_input_stream *stream = (void *)php_stream;
    int64_t length = 0;
    aws_crt_input_stream_get_length(stream, &length);
    RETURN_LONG(length);
}

PHP_FUNCTION(aws_crt_http_message_new_from_blob) {
    const char *blob = NULL;
    size_t blob_len = 0;

    aws_php_parse_parameters("s", &blob, &blob_len);

    aws_crt_http_message *message = aws_crt_http_message_new_from_blob((uint8_t *)blob, blob_len);
    RETURN_LONG((zend_ulong)message);
}

PHP_FUNCTION(aws_crt_http_message_to_blob) {
    zend_ulong php_msg = 0;

    aws_php_parse_parameters("l", &php_msg);

    aws_crt_http_message *message = (void *)php_msg;
    uint8_t *blob = NULL;
    size_t blob_len = 0;
    aws_crt_http_message_to_blob(message, &blob, &blob_len);
    AWS_RETURN_STRINGL((const char *)blob, blob_len);
    aws_crt_mem_release(blob);
}

PHP_FUNCTION(aws_crt_http_message_release) {
    zend_ulong php_msg = 0;

    aws_php_parse_parameters("l", &php_msg);

    aws_crt_http_message *message = (void *)php_msg;
    aws_crt_http_message_release(message);
}

PHP_FUNCTION(aws_crt_credentials_options_new) {
    aws_crt_credentials_options *options = aws_crt_credentials_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_credentials_options_release) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_release(options);
}

PHP_FUNCTION(aws_crt_credentials_options_set_access_key_id) {
    zend_ulong php_options = 0;
    const char *access_key_id = NULL;
    size_t access_key_id_len = 0;

    aws_php_parse_parameters("ls", &php_options, &access_key_id, &access_key_id_len);

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_access_key_id(options, (uint8_t *)access_key_id, access_key_id_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_secret_access_key) {
    zend_ulong php_options = 0;
    const char *secret_access_key = NULL;
    size_t secret_access_key_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ls", &php_options, &secret_access_key, &secret_access_key_len) ==
        FAILURE) {
        RETURN_NULL();
    }

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_secret_access_key(options, (uint8_t *)secret_access_key, secret_access_key_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_session_token) {
    zend_ulong php_options = 0;
    const char *session_token = NULL;
    size_t session_token_len = 0;

    aws_php_parse_parameters("ls", &php_options, &session_token, &session_token_len);

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_session_token(options, (uint8_t *)session_token, session_token_len);
}

PHP_FUNCTION(aws_crt_credentials_options_set_expiration_timepoint_seconds) {
    zend_ulong php_options = 0;
    zend_ulong expiration_timepoint_seconds = 0;
    aws_php_parse_parameters("ll", &php_options, &expiration_timepoint_seconds);

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials_options_set_expiration_timepoint_seconds(options, expiration_timepoint_seconds);
}

PHP_FUNCTION(aws_crt_credentials_new) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

    aws_crt_credentials_options *options = (void *)php_options;
    aws_crt_credentials *credentials = aws_crt_credentials_new(options);
    RETURN_LONG((zend_ulong)credentials);
}

PHP_FUNCTION(aws_crt_credentials_release) {
    zend_ulong php_credentials = 0;

    aws_php_parse_parameters("l", &php_credentials);

    aws_crt_credentials *credentials = (void *)php_credentials;
    aws_crt_credentials_release(credentials);
}

PHP_FUNCTION(aws_crt_credentials_provider_release) {
    zend_ulong php_creds_provider = 0;

    aws_php_parse_parameters("l", &php_creds_provider);

    aws_crt_credentials_provider *provider = (void *)php_creds_provider;
    aws_crt_credentials_provider_release(provider);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_new) {
    aws_crt_credentials_provider_static_options *options = aws_crt_credentials_provider_static_options_new();
    RETURN_LONG((zend_ulong)options);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_release) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider_static_options_release(options);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_access_key_id) {
    zend_ulong php_options = 0;
    const char *access_key_id = NULL;
    size_t access_key_id_len = 0;

    aws_php_parse_parameters("ls", &php_options, &access_key_id, &access_key_id_len);

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider_static_options_set_access_key_id(options, (uint8_t *)access_key_id, access_key_id_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_options_set_secret_access_key) {
    zend_ulong php_options = 0;
    const char *secret_access_key = NULL;
    size_t secret_access_key_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ls", &php_options, &secret_access_key, &secret_access_key_len) ==
        FAILURE) {
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

    aws_php_parse_parameters("ls", &php_options, &session_token, &session_token_len);

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider_static_options_set_session_token(options, (uint8_t *)session_token, session_token_len);
}

PHP_FUNCTION(aws_crt_credentials_provider_static_new) {
    zend_ulong php_options = 0;

    aws_php_parse_parameters("l", &php_options);

    aws_crt_credentials_provider_static_options *options = (void *)php_options;
    aws_crt_credentials_provider *provider = aws_crt_credentials_provider_static_new(options);
    RETURN_LONG((zend_ulong)provider);
}

PHP_FUNCTION(aws_crt_signing_config_aws_new) {
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_NULL();
    }

    aws_crt_signing_config_aws *signing_config = aws_crt_signing_config_aws_new();
    RETURN_LONG((zend_ulong)signing_config);
}

PHP_FUNCTION(aws_crt_signing_config_aws_release) {
    zend_ulong php_signing_config = 0;

    aws_php_parse_parameters("l", &php_signing_config);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_release(signing_config);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_algorithm) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_algorithm = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_algorithm);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_algorithm algorithm = php_algorithm;
    aws_crt_signing_config_aws_set_algorithm(signing_config, algorithm);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_signature_type) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_signature_type = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_signature_type);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signature_type signature_type = php_signature_type;
    aws_crt_signing_config_aws_set_signature_type(signing_config, signature_type);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_credentials_provider) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_credentials_provider = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_credentials_provider);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_credentials_provider *credentials_provider = (void*)php_credentials_provider;
    aws_crt_signing_config_aws_set_credentials_provider(signing_config, credentials_provider);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_region) {
    zend_ulong php_signing_config = 0;
    const char *region = NULL;
    size_t region_len = 0;

    aws_php_parse_parameters("ls", &php_signing_config, &region, &region_len);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_region(signing_config, (uint8_t*)region, region_len);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_service) {
    zend_ulong php_signing_config = 0;
    const char *service = NULL;
    size_t service_len = 0;

    aws_php_parse_parameters("ls", &php_signing_config, &service, &service_len);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_service(signing_config, (uint8_t*)service, service_len);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_use_double_uri_encode) {
    zend_ulong php_signing_config = 0;
    zend_bool php_use_double_uri_encode = 0;

    aws_php_parse_parameters("lb", &php_signing_config, &php_use_double_uri_encode);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_use_double_uri_encode(signing_config, php_use_double_uri_encode);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_should_normalize_uri_path) {
    zend_ulong php_signing_config = 0;
    zend_bool php_should_normalize_uri_path = 0;

    aws_php_parse_parameters("lb", &php_signing_config, &php_should_normalize_uri_path);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_should_normalize_uri_path(signing_config, php_should_normalize_uri_path);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_omit_session_token) {
    zend_ulong php_signing_config = 0;
    zend_bool php_omit_session_token = 0;

    aws_php_parse_parameters("lb", &php_signing_config, &php_omit_session_token);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_omit_session_token(signing_config, php_omit_session_token);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_signed_body_value) {
    zend_ulong php_signing_config = 0;
    const char *signed_body_value = NULL;
    size_t signed_body_value_len = 0;

    aws_php_parse_parameters("ls", &php_signing_config, &signed_body_value, &signed_body_value_len);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_signed_body_value(signing_config, (uint8_t*)signed_body_value, signed_body_value_len);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_signed_body_header_type) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_signed_body_header_type = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_signed_body_header_type);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signed_body_header_type signed_body_header_type = php_signed_body_header_type;
    aws_crt_signing_config_aws_set_signed_body_header_type(signing_config, signed_body_header_type);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_expiration_in_seconds) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_expiration_in_seconds = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_expiration_in_seconds);

    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    aws_crt_signing_config_aws_set_expiration_in_seconds(signing_config, php_expiration_in_seconds);
}

PHP_FUNCTION(aws_crt_signable_new_from_http_request) {
    zend_ulong php_http_message = 0;

    const aws_crt_http_message *http_message = (void*)php_http_message;
    aws_crt_signable *signable = aws_crt_signable_new_from_http_request(http_message);
    RETURN_LONG((zend_ulong)signable);
}

PHP_FUNCTION(aws_crt_signable_new_from_chunk) {
    zend_ulong php_input_stream = 0;
    const char *previous_signature = NULL;
    size_t previous_signature_len = 0;

    aws_php_parse_parameters("ls", &php_input_stream, &previous_signature, &previous_signature_len);

    aws_crt_input_stream *input_stream = (void*)php_input_stream;
    aws_crt_signable *signable = aws_crt_signable_new_from_chunk(input_stream, (uint8_t*)previous_signature, previous_signature_len);
    RETURN_LONG((zend_ulong)signable);
}

PHP_FUNCTION(aws_crt_signable_new_from_canonical_request) {
    const char *canonical_request = NULL;
    size_t canonical_request_len = 0;

    aws_crt_signable *signable = aws_crt_signable_new_from_canonical_request((uint8_t*)canonical_request, canonical_request_len);
    RETURN_LONG((zend_ulong)signable);
}

PHP_FUNCTION(aws_crt_signable_release) {
    zend_ulong php_signable = 0;

    aws_php_parse_parameters("l", &php_signable);

    aws_crt_signable *signable = (void*)php_signable;
    aws_crt_signable_release(signable);
}

static void s_on_sign_request_aws_complete(aws_crt_signing_result *result, int error_code, void *user_data) {
    zval *on_complete = user_data;

    aws_php_invoke_callback(on_complete, "ll", (zend_ulong)result, (zend_ulong)error_code);
}

PHP_FUNCTION(aws_crt_sign_request_aws) {
    zend_ulong php_signable = 0;
    zend_ulong php_signing_config = 0;
    zval *php_on_complete = 0;

    aws_php_parse_parameters("llz", &php_signable, &php_signing_config, &php_on_complete);

    aws_crt_signable *signable = (void*)php_signable;
    aws_crt_signing_config_aws *signing_config = (void*)php_signing_config;
    int ret = aws_crt_sign_request_aws(signable, signing_config, s_on_sign_request_aws_complete, php_on_complete);
    RETURN_LONG(ret);
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
