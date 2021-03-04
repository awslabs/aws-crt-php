<?php

/** @generate-class-entries */

function aws_crt_last_error(): int {}

function aws_crt_error_name(int $error_code): string {}

function aws_crt_error_str(int $error_code): string {}

function aws_crt_error_debug_str(int $error_code): string {}

function aws_crt_event_loop_group_new(int $max_threads): int {}

function aws_crt_event_loop_group_release(int $event_loop_group): void {}
