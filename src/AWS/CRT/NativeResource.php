<?php

namespace AWS\CRT;

use AWS\CRT\CRT as CRT;

/**
 * Base class for all native resources, tracks all outstanding resources
 * and provides basic leak checking
 */
abstract class NativeResource {
    protected static $crt = null;
    protected static $resources = [];
    protected $native = null;

    function __construct() {
        if (is_null(self::$crt)) {
            self::$crt = new CRT();
        }

        self::$resources[spl_object_hash($this)] = 1;
    }

    protected function acquire($handle) {
        $this->native = $handle;
    }

    protected function release() {
        $this->native = null;
    }

    function __destruct() {
        // Should have been destroyed and released by derived resource
        assert($this->native == null);
        unset(self::$resources[spl_object_hash($this)]);
    }
}
