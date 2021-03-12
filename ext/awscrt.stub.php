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
