<?php

/**
 * @generate-class-entries
 * @generate-function-entries
*/

function aws_crt_last_error(): int {}

function aws_crt_error_name(int $error_code): string {}

function aws_crt_error_str(int $error_code): string {}

function aws_crt_error_debug_str(int $error_code): string {}

function aws_crt_event_loop_group_options_new(): int {}

function aws_crt_event_loop_group_options_release(int $elg_options): void {}

function aws_crt_event_loop_group_options_set_max_threads(int $elg_options, int $max_threads): void {}

function aws_crt_event_loop_group_new(object $options): object {}

function aws_crt_event_loop_group_release(object $event_loop_group): void {}

function aws_crt_input_stream_options_new(): object {}

function aws_crt_input_stream_options_release(object $options): void {}

function aws_crt_input_stream_options_set_user_data(object $options, object $user_data): void {}

function aws_crt_input_stream_new(object $options): object {}

function aws_crt_input_stream_release(int $stream): void {}

function aws_crt_input_stream_seek(int $stream, int $offset, int $basis): int {}

function aws_crt_input_stream_read(int $stream, int $length): string {}

function aws_crt_input_stream_eof(int $stream): bool {}

function aws_crt_input_stream_get_length(int $stream): int {}

function aws_crt_http_message_new_from_blob(string $blob): int {}

function aws_crt_http_message_to_blob(int $message): string {}

function aws_crt_http_message_release(int $message): void {}

function aws_crt_credentials_options_new(): object {}

function aws_crt_credentials_options_release(object $options): void {}

function aws_crt_credentials_options_set_access_key_id(object $options, string $access_key_id): void {}

function aws_crt_credentials_options_set_secret_access_key(object $options, string $secret_access_key): void {}

function aws_crt_credentials_options_set_session_token(object $options, string $session_token): void {}

function aws_crt_credentials_options_set_expiration_timepoint_seconds(object $options, int $expiration_timepoint_seconds): void {}

function aws_crt_credentials_new(object $options): object {}

function aws_crt_credentials_release(object $credentials): void {}

function aws_crt_credentials_provider_release(int $credentials): void {}

function aws_crt_credentials_provider_static_options_new(): object {}

function aws_crt_credentials_provider_static_options_release(object $options): void {}

function aws_crt_credentials_provider_static_options_set_access_key_id(object $options, string $access_key_id): void {}

function aws_crt_credentials_provider_static_options_set_secret_access_key(object $options, string $secret_access_key): void {}

function aws_crt_credentials_provider_static_options_set_session_token(object $options, string $session_token): void {}

function aws_crt_credentials_provider_static_new(object $options): object {}
