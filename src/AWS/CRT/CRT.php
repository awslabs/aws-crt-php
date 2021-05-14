<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
namespace AWS\CRT;

use AWS\CRT\Internal\Extension;

use \RuntimeException;

/**
 * Wrapper for the interface to the CRT. There only ever needs to be one of these, but
 * additional instances won't cost anything other than their memory.
 * Creating an instance of any NativeResource will activate the CRT binding. User code
 * should only need to create one of these if they are only accessing CRT:: static functions.
 */
final class CRT {

    private static $impl = null;
    private static $refcount = 0;

    function __construct() {
        if (is_null(self::$impl)) {
            // Figure out what backends are/should be available
            $backends = ['Extension'];

            // Try to load each backend, give up if none succeed
            $exceptions = [];
            foreach ($backends as $backend) {
                try {
                    $backend = 'AWS\\CRT\\Internal\\' . $backend;
                    self::$impl = new $backend();
                } catch (RuntimeException $rex) {
                    array_push($exceptions, $rex);
                }
            }
            if (is_null(self::$impl)) {
                throw new RuntimeException('Unable to initialize AWS CRT via ' . join(', ', $backends) . ": \n" . join("\n", $exceptions), -1);
            }
        }
        ++self::$refcount;
    }

    function __destruct() {
        if (--self::$refcount == 0) {
            self::$impl = null;
        }
    }

    /**
     * @return integer last error code reported within the CRT
     */
    public static function last_error() {
        return self::$impl->aws_crt_last_error();
    }

    /**
     * @param integer $error Error code from the CRT, usually delivered via callback or {@see last_error}
     * @return string Human-readable description of the provided error code
     */
    public static function error_str($error) {
        return self::$impl->aws_crt_error_str((int) $error);
    }

    /**
     * @param integer $error Error code from the CRT, usually delivered via callback or {@see last_error}
     * @return string Name/enum identifier for the provided error code
     */
    public static function error_name($error) {
        return self::$impl->aws_crt_error_name((int) $error);
    }

    /**
     * @return object Pointer to native event_loop_group_options
     */
    function event_loop_group_options_new() {
        return self::$impl->aws_crt_event_loop_group_options_new();
    }

    /**
     * @param object $elg_options Pointer to native event_loop_group_options
     */
    function event_loop_group_options_release($elg_options) {
        self::$impl->aws_crt_event_loop_group_options_release($elg_options);
    }

    /**
     * @param object $elg_options Pointer to native event_loop_group_options
     * @param integer $max_threads Maximum number of threads to allow the event loop group to use, default: 0/1 per CPU core
     */
    function event_loop_group_options_set_max_threads($elg_options, $max_threads) {
        self::$impl->aws_crt_event_loop_group_options_set_max_threads($elg_options, (int)$max_threads);
    }

    /**
     * @param object Pointer to event_loop_group_options, {@see event_loop_group_options_new}
     * @return object Pointer to the new event loop group
     */
    function event_loop_group_new($options) {
        return self::$impl->aws_crt_event_loop_group_new($options);
    }

    /**
     * @param object $elg Pointer to the event loop group to release
     */
    function event_loop_group_release($elg) {
        self::$impl->aws_crt_event_loop_group_release($elg);
    }

    /**
     * return object Pointer to native AWS credentials options
     */
    function aws_credentials_options_new() {
        return self::$impl->aws_crt_credentials_options_new();
    }

    function aws_credentials_options_release($options) {
        self::$impl->aws_crt_credentials_options_release($options);
    }

    function aws_credentials_options_set_access_key_id($options, $access_key_id) {
        self::$impl->aws_crt_credentials_options_set_access_key_id($options, $access_key_id);
    }

    function aws_credentials_options_set_secret_access_key($options, $secret_access_key) {
        self::$impl->aws_crt_credentials_options_set_secret_access_key($options, $secret_access_key);
    }

    function aws_credentials_options_set_session_token($options, $session_token) {
        self::$impl->aws_crt_credentials_options_set_session_token($options, $session_token);
    }

    function aws_credentials_options_set_expiration_timepoint_seconds($options, $expiration_timepoint_seconds) {
        self::$impl->aws_crt_credentials_options_set_expiration_timepoint_seconds($options, $expiration_timepoint_seconds);
    }

    function aws_credentials_new($options) {
        return self::$impl->aws_crt_credentials_new($options);
    }

    function aws_credentials_release($credentials) {
        self::$impl->aws_crt_credentials_release($credentials);
    }

    function credentials_provider_release($provider) {
        self::$impl->aws_crt_credentials_provider_release($provider);
    }

    function credentials_provider_static_options_new() {
        return self::$impl->aws_crt_credentials_provider_static_options_new();
    }

    function credentials_provider_static_options_release($options) {
        self::$impl->aws_crt_credentials_provider_static_options_release($options);
    }

    function credentials_provider_static_options_set_access_key_id($options, $access_key_id) {
        self::$impl->aws_crt_credentials_provider_static_options_set_access_key_id($options, $access_key_id);
    }

    function credentials_provider_static_options_set_secret_access_key($options, $secret_access_key) {
        self::$impl->aws_crt_credentials_provider_static_options_set_secret_access_key($options, $secret_access_key);
    }

    function credentials_provider_static_options_set_session_token($options, $session_token) {
        self::$impl->aws_crt_credentials_provider_static_options_set_session_token($options, $session_token);
    }

    function credentials_provider_static_new($options) {
        return self::$impl->aws_crt_credentials_provider_static_new($options);
    }

    function input_stream_options_new() {
        return self::$impl->aws_crt_input_stream_options_new();
    }

    function input_stream_options_release($options) {
        self::$impl->aws_crt_input_stream_options_release($options);
    }

    function input_stream_options_set_user_data($options, $user_data) {
        self::$impl->aws_crt_input_stream_options_set_user_data($options, $user_data);
    }

    function input_stream_new($options) {
        return self::$impl->aws_crt_input_stream_new($options);
    }

    function input_stream_release($stream) {
        self::$impl->aws_crt_input_stream_release($stream);
    }

    function input_stream_seek($stream, $offset, $basis) {
        return self::$impl->aws_crt_input_stream_seek($stream, $offset, $basis);
    }

    function input_stream_read($stream, $length) {
        return self::$impl->aws_crt_input_stream_read($stream, $length);
    }

    function input_stream_eof($stream) {
        return self::$impl->aws_crt_input_stream_eof($stream);
    }

    function input_stream_get_length($stream) {
        return self::$impl->aws_crt_input_stream_get_length($stream);
    }

    function http_message_new_from_blob($blob) {
        return self::$impl->aws_crt_http_message_new_from_blob($blob);
    }

    function http_message_release($message) {
        self::$impl->aws_crt_http_message_release($message);
    }

    function signing_config_aws_new() {
        return self::$impl->aws_crt_signing_config_aws_new();
    }

    function signing_config_aws_release($signing_config) {
        return self::$impl->aws_crt_signing_config_aws_release($signing_config);
    }

    function signing_config_aws_set_algorithm($signing_config, $algorithm) {
        self::$impl->aws_crt_signing_config_aws_set_algorithm($signing_config, (int)$algorithm);
    }

    function signing_config_aws_set_signature_type($signing_config, $signature_type) {
        self::$impl->aws_crt_signing_config_aws_set_signature_type($signing_config, (int)$signature_type);
    }

    function signing_config_aws_set_credentials_provider($signing_config, $credentials_provider) {
        self::$impl->aws_crt_signing_config_aws_set_credentials_provider($signing_config, $credentials_provider);
    }

    function signing_config_aws_set_region($signing_config, $region) {
        self::$impl->aws_crt_signing_config_aws_set_region($signing_config, $region);
    }

    function signing_config_aws_set_service($signing_config, $service) {
        self::$impl->aws_crt_signing_config_aws_set_service($signing_config, $service);
    }

    function signing_config_aws_set_use_double_uri_encode($signing_config, $use_double_uri_encode) {
        self::$impl->aws_crt_signing_config_aws_set_use_double_uri_encode($signing_config, $use_double_uri_encode);
    }

    function signing_config_aws_set_should_normalize_uri_path($signing_config, $should_normalize_uri_path) {
        self::$impl->aws_crt_signing_config_aws_set_should_normalize_uri_path($signing_config, $should_normalize_uri_path);
    }

    function signing_config_aws_set_omit_session_token($signing_config, $omit_session_token) {
        self::$impl->aws_crt_signing_config_aws_set_omit_session_token($signing_config, $omit_session_token);
    }

    function signing_config_aws_set_signed_body_value($signing_config, $signed_body_value) {
        self::$impl->aws_crt_signing_config_aws_set_signed_body_value($signing_config, $signed_body_value);
    }

    function signing_config_aws_set_signed_body_header_type($signing_config, $signed_body_header_type) {
        self::$impl->aws_crt_signing_config_aws_set_signed_body_header_type($signing_config, $signed_body_header_type);
    }

    function signing_config_aws_set_expiration_in_seconds($signing_config, $expiration_in_seconds) {
        self::$impl->aws_crt_signing_config_aws_set_expiration_in_seconds($signing_config, $expiration_in_seconds);
    }

    function signable_new_from_http_request($http_message) {
        return self::$impl->aws_crt_signable_new_from_http_request($http_message);
    }

    function signable_new_from_chunk($chunk_stream, $previous_signature) {
        return self::$impl->aws_crt_signable_new_from_chunk($chunk_stream, $previous_signature);
    }

    function signable_new_from_canonical_request($canonical_request) {
        return self::$impl->aws_crt_signable_new_from_canonical_request($canonical_request);
    }

    function sign_request_aws($signable, $signing_config, $on_complete) {
        return self::$impl->aws_crt_sign_request_aws($signable, $signing_config, $on_complete);
    }
}
