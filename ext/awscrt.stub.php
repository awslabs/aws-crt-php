<?php

/** @generate-class-entries */

function aws_crt_last_error(): int {}

function aws_crt_error_name(int $error_code): string {}

function aws_crt_error_str(int $error_code): string {}

function aws_crt_error_debug_str(int $error_code): string {}

function aws_crt_event_loop_group_options_new(): object {}

function aws_crt_event_loop_group_options_release(object $elg_options): void {}

function aws_crt_event_loop_group_options_set_max_threads(object $elg_options, int $max_threads): void {}

function aws_crt_event_loop_group_new(object $options): object {}

function aws_crt_event_loop_group_release(object $event_loop_group): void {}

function aws_crt_credentials_options_new(): object {}

function aws_crt_credentials_options_release(object $options): void {}

function aws_crt_credentials_options_set_access_key_id(object $options, string $access_key_id): void {}

function aws_crt_credentials_options_set_secret_access_key(object $options, string $secret_access_key): void {}

function aws_crt_credentials_options_set_session_token(object $options, string $session_token): void {}

function aws_crt_credentials_options_set_expiration_timepoint_seconds(object $options, int $expiration_timepoint_seconds): void {}

function aws_crt_credentials_new(object $options): object {}

function aws_crt_credentials_release(object $credentials): void {}

function aws_crt_credentials_provider_release(object $credentials): void {}

function aws_crt_credentials_provider_static_options_new(): object {}

function aws_crt_credentials_provider_static_options_release(object $options): void {}

function aws_crt_credentials_provider_static_options_set_access_key_id(object $options, string $access_key_id): void {}

function aws_crt_credentials_provider_static_options_set_secret_access_key(object $options, string $secret_access_key): void {}

function aws_crt_credentials_provider_static_options_set_session_token(object $options, string $session_token): void {}

function aws_crt_credentials_provider_static_new(object $options): object {}
