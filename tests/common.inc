<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\CRT as CRT;
use Yoast\PHPUnitPolyfills\TestCases\TestCase;

ini_set("memory_limit", "512M");

abstract class CrtTestCase extends TestCase {
    private static $crt = null;
    public static function set_up_before_class() {
        parent::set_up_before_class();
        self::$crt = new CRT();
    }

    public static function tear_down_after_class() {
        self::$crt = null;
        parent::tear_down_after_class();
    }

    // Ensure that after every test there are no errors in the CRT itself
    protected function assert_post_conditions() {
        if (CRT::last_error()) {
            $this->fail("Test left an error on the stack: " . CRT::error_name(CRT::last_error()));
        }
        parent::assert_post_conditions();
    }
}
