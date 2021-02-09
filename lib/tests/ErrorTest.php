<?php

require_once('tests.inc');

final class ErrorTest extends PHPUnit_Framework_TestCase {
    private static $crt = null;
    public static function setUpBeforeClass() {
        self::$crt = new CRT();
    }

    public static function tearDownAfterClass() {
        self::$crt = null;
    }

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
