/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include "php_aws_crt.h"

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

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_release(signing_config);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_algorithm) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_algorithm = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_algorithm);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_algorithm algorithm = php_algorithm;
    aws_crt_signing_config_aws_set_algorithm(signing_config, algorithm);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_signature_type) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_signature_type = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_signature_type);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signature_type signature_type = php_signature_type;
    aws_crt_signing_config_aws_set_signature_type(signing_config, signature_type);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_credentials_provider) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_credentials_provider = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_credentials_provider);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_credentials_provider *credentials_provider = (void *)php_credentials_provider;
    aws_crt_signing_config_aws_set_credentials_provider(signing_config, credentials_provider);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_region) {
    zend_ulong php_signing_config = 0;
    const char *region = NULL;
    size_t region_len = 0;

    aws_php_parse_parameters("ls", &php_signing_config, &region, &region_len);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_region(signing_config, (uint8_t *)region, region_len);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_service) {
    zend_ulong php_signing_config = 0;
    const char *service = NULL;
    size_t service_len = 0;

    aws_php_parse_parameters("ls", &php_signing_config, &service, &service_len);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_service(signing_config, (uint8_t *)service, service_len);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_use_double_uri_encode) {
    zend_ulong php_signing_config = 0;
    zend_bool php_use_double_uri_encode = 0;

    aws_php_parse_parameters("lb", &php_signing_config, &php_use_double_uri_encode);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_use_double_uri_encode(signing_config, php_use_double_uri_encode);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_should_normalize_uri_path) {
    zend_ulong php_signing_config = 0;
    zend_bool php_should_normalize_uri_path = 0;

    aws_php_parse_parameters("lb", &php_signing_config, &php_should_normalize_uri_path);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_should_normalize_uri_path(signing_config, php_should_normalize_uri_path);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_omit_session_token) {
    zend_ulong php_signing_config = 0;
    zend_bool php_omit_session_token = 0;

    aws_php_parse_parameters("lb", &php_signing_config, &php_omit_session_token);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_omit_session_token(signing_config, php_omit_session_token);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_signed_body_value) {
    zend_ulong php_signing_config = 0;
    const char *signed_body_value = NULL;
    size_t signed_body_value_len = 0;

    aws_php_parse_parameters("ls", &php_signing_config, &signed_body_value, &signed_body_value_len);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_signed_body_value(
        signing_config, (uint8_t *)signed_body_value, signed_body_value_len);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_signed_body_header_type) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_signed_body_header_type = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_signed_body_header_type);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signed_body_header_type signed_body_header_type = php_signed_body_header_type;
    aws_crt_signing_config_aws_set_signed_body_header_type(signing_config, signed_body_header_type);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_expiration_in_seconds) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_expiration_in_seconds = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_expiration_in_seconds);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_expiration_in_seconds(signing_config, php_expiration_in_seconds);
}

PHP_FUNCTION(aws_crt_signing_config_aws_set_date) {
    zend_ulong php_signing_config = 0;
    zend_ulong php_timestamp = 0;

    aws_php_parse_parameters("ll", &php_signing_config, &php_timestamp);

    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;
    aws_crt_signing_config_aws_set_date(signing_config, php_timestamp);
}

PHP_FUNCTION(aws_crt_signable_new_from_http_request) {
    zend_ulong php_http_message = 0;

    aws_php_parse_parameters("l", &php_http_message);

    const aws_crt_http_message *http_message = (void *)php_http_message;
    aws_crt_signable *signable = aws_crt_signable_new_from_http_request(http_message);
    RETURN_LONG((zend_ulong)signable);
}

PHP_FUNCTION(aws_crt_signable_new_from_chunk) {
    zend_ulong php_input_stream = 0;
    const char *previous_signature = NULL;
    size_t previous_signature_len = 0;

    aws_php_parse_parameters("ls", &php_input_stream, &previous_signature, &previous_signature_len);

    aws_crt_input_stream *input_stream = (void *)php_input_stream;
    aws_crt_signable *signable =
        aws_crt_signable_new_from_chunk(input_stream, (uint8_t *)previous_signature, previous_signature_len);
    RETURN_LONG((zend_ulong)signable);
}

PHP_FUNCTION(aws_crt_signable_new_from_canonical_request) {
    const char *canonical_request = NULL;
    size_t canonical_request_len = 0;

    aws_crt_signable *signable =
        aws_crt_signable_new_from_canonical_request((uint8_t *)canonical_request, canonical_request_len);
    RETURN_LONG((zend_ulong)signable);
}

PHP_FUNCTION(aws_crt_signable_release) {
    zend_ulong php_signable = 0;

    aws_php_parse_parameters("l", &php_signable);

    aws_crt_signable *signable = (void *)php_signable;
    aws_crt_signable_release(signable);
}

PHP_FUNCTION(aws_crt_signing_result_release) {
    zend_ulong php_signing_result = 0;

    aws_php_parse_parameters("l", &php_signing_result);
    aws_crt_signing_result *result = (void *)php_signing_result;
    aws_crt_signing_result_release(result);
}

PHP_FUNCTION(aws_crt_signing_result_apply_to_http_request) {
    zend_ulong php_signing_result = 0;
    zend_ulong php_http_request = 0;

    aws_php_parse_parameters("ll", &php_signing_result, &php_http_request);
    aws_crt_signing_result *result = (void *)php_signing_result;
    aws_crt_http_message *request = (void *)php_http_request;

    if (aws_crt_signing_result_apply_to_http_request(result, request)) {
        aws_php_throw_exception(
            "Failed to apply signing result to HTTP request: %s", aws_crt_error_name(aws_crt_last_error()));
    }
}

typedef struct _signing_state {
    struct aws_promise *promise;
    zval *on_complete;
    aws_crt_signing_result *signing_result;
    int error_code;
} signing_state;

/* called on main thread to deliver result to php */
static void s_sign_aws_complete(void *data) {
    signing_state *state = data;
    zval *on_complete = state->on_complete;
    aws_php_invoke_callback(on_complete, "ll", (zend_ulong)state->signing_result, (zend_ulong)state->error_code);
}

/* called from signing process in aws_sign_request_aws */
static void s_on_sign_request_aws_complete(aws_crt_signing_result *result, int error_code, void *user_data) {
    signing_state *state = user_data;
    struct aws_promise *promise = state->promise;

    state->signing_result = result;
    state->error_code = error_code;

    /*
     * Must execute PHP callback before this function returns, or signing_result will be killed
     * so the callback is queued back to the main thread and will have run when yield returns
     */
    aws_php_task complete_callback_task = {
        .callback = s_sign_aws_complete,
        .data = state,
    };
    aws_php_thread_queue_push(&s_aws_php_main_thread_queue, complete_callback_task);
    aws_php_thread_queue_yield(&s_aws_php_main_thread_queue);

    if (error_code) {
        aws_promise_fail(promise, error_code);
    } else {
        aws_promise_complete(promise, result, NULL);
    }
}

PHP_FUNCTION(aws_crt_sign_request_aws) {
    zend_ulong php_signable = 0;
    zend_ulong php_signing_config = 0;
    zval *php_on_complete = 0;
    zend_ulong php_user_data = 0;

    aws_php_parse_parameters("llzl", &php_signable, &php_signing_config, &php_on_complete, &php_user_data);

    aws_crt_signable *signable = (void *)php_signable;
    aws_crt_signing_config_aws *signing_config = (void *)php_signing_config;

    struct aws_promise *promise = aws_promise_new(aws_crt_default_allocator());
    signing_state state = {
        .promise = promise,
        .on_complete = php_on_complete,
    };
    int ret = aws_crt_sign_request_aws(signable, signing_config, s_on_sign_request_aws_complete, &state);
    if (ret != 0) {
        int last_error = aws_crt_last_error();
        aws_promise_fail(promise, last_error);
        aws_php_throw_exception(
            "aws_crt_sign_request_aws: error starting signing process: %s", aws_crt_error_name(last_error));
    }

    aws_php_thread_queue_wait(&s_aws_php_main_thread_queue, promise);

done:
    aws_promise_release(promise);
    RETURN_LONG(ret);
}
