<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\CRT;
use Yoast\PHPUnitPolyfills\TestCases\TestCase;

final class ErrorTest extends TestCase {

    public function testNoInitialError() {
        $this->assertEquals(0, CRT::last_error());
    }

    public function testCanResolveErrorName() {
        $this->assertEquals("AWS_ERROR_SUCCESS", CRT::error_name(0));
    }

    public function testCanResolveErrorStr() {
        $this->assertEquals("Success.", CRT::error_str(0));
    }
}
