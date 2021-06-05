/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 8ee94b778eb6d2eeabc8c2695aaded9fb18de88f */

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_last_error, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_error_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, error_code, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_error_str arginfo_aws_crt_error_name

#define arginfo_aws_crt_error_debug_str arginfo_aws_crt_error_name

#define arginfo_aws_crt_event_loop_group_options_new arginfo_aws_crt_last_error

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_options_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, elg_options, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_options_set_max_threads, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, elg_options, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_threads, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_new, 0, 1, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, event_loop_group, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_options_new, 0, 0, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_options_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_options_set_user_data, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, user_data, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_input_stream_new arginfo_aws_crt_event_loop_group_new

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_seek, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, basis, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_read, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_eof, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_input_stream_get_length, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_http_message_new_from_blob, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blob, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_http_message_to_blob, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, message, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_http_message_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, message, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_credentials_options_new arginfo_aws_crt_input_stream_options_new

#define arginfo_aws_crt_credentials_options_release arginfo_aws_crt_input_stream_options_release

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_credentials_options_set_access_key_id, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, access_key_id, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_credentials_options_set_secret_access_key, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, secret_access_key, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_credentials_options_set_session_token, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, session_token, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_credentials_options_set_expiration_timepoint_seconds, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, expiration_timepoint_seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_credentials_new arginfo_aws_crt_event_loop_group_new

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_credentials_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, credentials, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_credentials_provider_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, credentials, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_credentials_provider_static_options_new arginfo_aws_crt_input_stream_options_new

#define arginfo_aws_crt_credentials_provider_static_options_release arginfo_aws_crt_input_stream_options_release

#define arginfo_aws_crt_credentials_provider_static_options_set_access_key_id arginfo_aws_crt_credentials_options_set_access_key_id

#define arginfo_aws_crt_credentials_provider_static_options_set_secret_access_key arginfo_aws_crt_credentials_options_set_secret_access_key

#define arginfo_aws_crt_credentials_provider_static_options_set_session_token arginfo_aws_crt_credentials_options_set_session_token

#define arginfo_aws_crt_credentials_provider_static_new arginfo_aws_crt_event_loop_group_new

#define arginfo_aws_crt_signing_config_aws_new arginfo_aws_crt_last_error

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_algorithm, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, algorithm, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_signature_type, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, signature_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_credentials_provider, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, credentials_provider, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_region, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, region, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_service, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, service, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_use_double_uri_encode, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, use_double_uri_encode, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_should_normalize_uri_path, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, should_normalize_uri_path, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_omit_session_token, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, omit_session_token, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_signed_body_value, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, signed_body_value, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_signed_body_header_type, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, signed_body_header_type, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_expiration_in_seconds, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, expiration_in_seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_config_aws_set_date, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, timestamp, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signable_new_from_http_request, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, http_message, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signable_new_from_chunk, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, input_stream, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, previous_signature, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signable_new_from_canonical_request, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, request, IS_STRING, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signable_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, signable, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_result_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, signing_result, IS_LONG, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_signing_result_apply_to_http_request, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, signing_result, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, http_request, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

AWS_PHP_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_sign_request_aws, 0, 4, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, signable, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, signing_config, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, on_complete, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, user_data, IS_OBJECT, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(aws_crt_last_error);
ZEND_FUNCTION(aws_crt_error_name);
ZEND_FUNCTION(aws_crt_error_str);
ZEND_FUNCTION(aws_crt_error_debug_str);
ZEND_FUNCTION(aws_crt_event_loop_group_options_new);
ZEND_FUNCTION(aws_crt_event_loop_group_options_release);
ZEND_FUNCTION(aws_crt_event_loop_group_options_set_max_threads);
ZEND_FUNCTION(aws_crt_event_loop_group_new);
ZEND_FUNCTION(aws_crt_event_loop_group_release);
ZEND_FUNCTION(aws_crt_input_stream_options_new);
ZEND_FUNCTION(aws_crt_input_stream_options_release);
ZEND_FUNCTION(aws_crt_input_stream_options_set_user_data);
ZEND_FUNCTION(aws_crt_input_stream_new);
ZEND_FUNCTION(aws_crt_input_stream_release);
ZEND_FUNCTION(aws_crt_input_stream_seek);
ZEND_FUNCTION(aws_crt_input_stream_read);
ZEND_FUNCTION(aws_crt_input_stream_eof);
ZEND_FUNCTION(aws_crt_input_stream_get_length);
ZEND_FUNCTION(aws_crt_http_message_new_from_blob);
ZEND_FUNCTION(aws_crt_http_message_to_blob);
ZEND_FUNCTION(aws_crt_http_message_release);
ZEND_FUNCTION(aws_crt_credentials_options_new);
ZEND_FUNCTION(aws_crt_credentials_options_release);
ZEND_FUNCTION(aws_crt_credentials_options_set_access_key_id);
ZEND_FUNCTION(aws_crt_credentials_options_set_secret_access_key);
ZEND_FUNCTION(aws_crt_credentials_options_set_session_token);
ZEND_FUNCTION(aws_crt_credentials_options_set_expiration_timepoint_seconds);
ZEND_FUNCTION(aws_crt_credentials_new);
ZEND_FUNCTION(aws_crt_credentials_release);
ZEND_FUNCTION(aws_crt_credentials_provider_release);
ZEND_FUNCTION(aws_crt_credentials_provider_static_options_new);
ZEND_FUNCTION(aws_crt_credentials_provider_static_options_release);
ZEND_FUNCTION(aws_crt_credentials_provider_static_options_set_access_key_id);
ZEND_FUNCTION(aws_crt_credentials_provider_static_options_set_secret_access_key);
ZEND_FUNCTION(aws_crt_credentials_provider_static_options_set_session_token);
ZEND_FUNCTION(aws_crt_credentials_provider_static_new);
ZEND_FUNCTION(aws_crt_signing_config_aws_new);
ZEND_FUNCTION(aws_crt_signing_config_aws_release);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_algorithm);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_signature_type);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_credentials_provider);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_region);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_service);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_use_double_uri_encode);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_should_normalize_uri_path);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_omit_session_token);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_signed_body_value);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_signed_body_header_type);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_expiration_in_seconds);
ZEND_FUNCTION(aws_crt_signing_config_aws_set_date);
ZEND_FUNCTION(aws_crt_signable_new_from_http_request);
ZEND_FUNCTION(aws_crt_signable_new_from_chunk);
ZEND_FUNCTION(aws_crt_signable_new_from_canonical_request);
ZEND_FUNCTION(aws_crt_signable_release);
ZEND_FUNCTION(aws_crt_signing_result_release);
ZEND_FUNCTION(aws_crt_signing_result_apply_to_http_request);
ZEND_FUNCTION(aws_crt_sign_request_aws);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(aws_crt_last_error, arginfo_aws_crt_last_error)
	ZEND_FE(aws_crt_error_name, arginfo_aws_crt_error_name)
	ZEND_FE(aws_crt_error_str, arginfo_aws_crt_error_str)
	ZEND_FE(aws_crt_error_debug_str, arginfo_aws_crt_error_debug_str)
	ZEND_FE(aws_crt_event_loop_group_options_new, arginfo_aws_crt_event_loop_group_options_new)
	ZEND_FE(aws_crt_event_loop_group_options_release, arginfo_aws_crt_event_loop_group_options_release)
	ZEND_FE(aws_crt_event_loop_group_options_set_max_threads, arginfo_aws_crt_event_loop_group_options_set_max_threads)
	ZEND_FE(aws_crt_event_loop_group_new, arginfo_aws_crt_event_loop_group_new)
	ZEND_FE(aws_crt_event_loop_group_release, arginfo_aws_crt_event_loop_group_release)
	ZEND_FE(aws_crt_input_stream_options_new, arginfo_aws_crt_input_stream_options_new)
	ZEND_FE(aws_crt_input_stream_options_release, arginfo_aws_crt_input_stream_options_release)
	ZEND_FE(aws_crt_input_stream_options_set_user_data, arginfo_aws_crt_input_stream_options_set_user_data)
	ZEND_FE(aws_crt_input_stream_new, arginfo_aws_crt_input_stream_new)
	ZEND_FE(aws_crt_input_stream_release, arginfo_aws_crt_input_stream_release)
	ZEND_FE(aws_crt_input_stream_seek, arginfo_aws_crt_input_stream_seek)
	ZEND_FE(aws_crt_input_stream_read, arginfo_aws_crt_input_stream_read)
	ZEND_FE(aws_crt_input_stream_eof, arginfo_aws_crt_input_stream_eof)
	ZEND_FE(aws_crt_input_stream_get_length, arginfo_aws_crt_input_stream_get_length)
	ZEND_FE(aws_crt_http_message_new_from_blob, arginfo_aws_crt_http_message_new_from_blob)
	ZEND_FE(aws_crt_http_message_to_blob, arginfo_aws_crt_http_message_to_blob)
	ZEND_FE(aws_crt_http_message_release, arginfo_aws_crt_http_message_release)
	ZEND_FE(aws_crt_credentials_options_new, arginfo_aws_crt_credentials_options_new)
	ZEND_FE(aws_crt_credentials_options_release, arginfo_aws_crt_credentials_options_release)
	ZEND_FE(aws_crt_credentials_options_set_access_key_id, arginfo_aws_crt_credentials_options_set_access_key_id)
	ZEND_FE(aws_crt_credentials_options_set_secret_access_key, arginfo_aws_crt_credentials_options_set_secret_access_key)
	ZEND_FE(aws_crt_credentials_options_set_session_token, arginfo_aws_crt_credentials_options_set_session_token)
	ZEND_FE(aws_crt_credentials_options_set_expiration_timepoint_seconds, arginfo_aws_crt_credentials_options_set_expiration_timepoint_seconds)
	ZEND_FE(aws_crt_credentials_new, arginfo_aws_crt_credentials_new)
	ZEND_FE(aws_crt_credentials_release, arginfo_aws_crt_credentials_release)
	ZEND_FE(aws_crt_credentials_provider_release, arginfo_aws_crt_credentials_provider_release)
	ZEND_FE(aws_crt_credentials_provider_static_options_new, arginfo_aws_crt_credentials_provider_static_options_new)
	ZEND_FE(aws_crt_credentials_provider_static_options_release, arginfo_aws_crt_credentials_provider_static_options_release)
	ZEND_FE(aws_crt_credentials_provider_static_options_set_access_key_id, arginfo_aws_crt_credentials_provider_static_options_set_access_key_id)
	ZEND_FE(aws_crt_credentials_provider_static_options_set_secret_access_key, arginfo_aws_crt_credentials_provider_static_options_set_secret_access_key)
	ZEND_FE(aws_crt_credentials_provider_static_options_set_session_token, arginfo_aws_crt_credentials_provider_static_options_set_session_token)
	ZEND_FE(aws_crt_credentials_provider_static_new, arginfo_aws_crt_credentials_provider_static_new)
	ZEND_FE(aws_crt_signing_config_aws_new, arginfo_aws_crt_signing_config_aws_new)
	ZEND_FE(aws_crt_signing_config_aws_release, arginfo_aws_crt_signing_config_aws_release)
	ZEND_FE(aws_crt_signing_config_aws_set_algorithm, arginfo_aws_crt_signing_config_aws_set_algorithm)
	ZEND_FE(aws_crt_signing_config_aws_set_signature_type, arginfo_aws_crt_signing_config_aws_set_signature_type)
	ZEND_FE(aws_crt_signing_config_aws_set_credentials_provider, arginfo_aws_crt_signing_config_aws_set_credentials_provider)
	ZEND_FE(aws_crt_signing_config_aws_set_region, arginfo_aws_crt_signing_config_aws_set_region)
	ZEND_FE(aws_crt_signing_config_aws_set_service, arginfo_aws_crt_signing_config_aws_set_service)
	ZEND_FE(aws_crt_signing_config_aws_set_use_double_uri_encode, arginfo_aws_crt_signing_config_aws_set_use_double_uri_encode)
	ZEND_FE(aws_crt_signing_config_aws_set_should_normalize_uri_path, arginfo_aws_crt_signing_config_aws_set_should_normalize_uri_path)
	ZEND_FE(aws_crt_signing_config_aws_set_omit_session_token, arginfo_aws_crt_signing_config_aws_set_omit_session_token)
	ZEND_FE(aws_crt_signing_config_aws_set_signed_body_value, arginfo_aws_crt_signing_config_aws_set_signed_body_value)
	ZEND_FE(aws_crt_signing_config_aws_set_signed_body_header_type, arginfo_aws_crt_signing_config_aws_set_signed_body_header_type)
	ZEND_FE(aws_crt_signing_config_aws_set_expiration_in_seconds, arginfo_aws_crt_signing_config_aws_set_expiration_in_seconds)
	ZEND_FE(aws_crt_signing_config_aws_set_date, arginfo_aws_crt_signing_config_aws_set_date)
	ZEND_FE(aws_crt_signable_new_from_http_request, arginfo_aws_crt_signable_new_from_http_request)
	ZEND_FE(aws_crt_signable_new_from_chunk, arginfo_aws_crt_signable_new_from_chunk)
	ZEND_FE(aws_crt_signable_new_from_canonical_request, arginfo_aws_crt_signable_new_from_canonical_request)
	ZEND_FE(aws_crt_signable_release, arginfo_aws_crt_signable_release)
	ZEND_FE(aws_crt_signing_result_release, arginfo_aws_crt_signing_result_release)
	ZEND_FE(aws_crt_signing_result_apply_to_http_request, arginfo_aws_crt_signing_result_apply_to_http_request)
	ZEND_FE(aws_crt_sign_request_aws, arginfo_aws_crt_sign_request_aws)
	ZEND_FE_END
};
