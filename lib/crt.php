<?php

// Wrapper for the FFI interface to the CRT. There only ever needs to be one of these.
final class CRT {
    private static $ffi = null;
    private static $refcount = 0;

    function __construct() {
        if (is_null(self::$ffi)) {
            try {
                self::$ffi = FFI::cdef(file_get_contents(__DIR__ . "/api.h"), __DIR__ . "/libaws-crt-ffi.so");
                self::init();
            } catch (Exception $e) {
                echo 'Exception while initializing CRT via FFI: ', $e->getMessage(), "\n";
            }
        }
        ++self::$refcount;
    }

    function __destruct() {
        if (--self::$refcount == 0) {
            self::clean_up();
            self::$ffi = null;
        }
    }

    // library lifetime
    private static function init() {
        return self::$ffi->aws_crt_init();
    }

    private static function clean_up() {
        return self::$ffi->aws_crt_clean_up();
    }

    // Error handling
    public static function last_error() {
        return self::$ffi->aws_crt_last_error();
    }

    public static function error_str($error) {
        return self::$ffi->aws_crt_error_str((int) $error);
    }

    public static function error_name($error) {
        return self::$ffi->aws_crt_error_name((int) $error);
    }

    // IO
    function event_loop_group_new($options) {
        return self::$ffi->aws_crt_event_loop_group_new($options->num_threads);
    }

    function event_loop_group_release($elg) {
        return self::$ffi->aws_crt_event_loop_group_release($elg);
    }
}

// Base class for all native resources, tracks all outstanding resources
// and provides basic leak checking
abstract class NativeResource {
    protected static $crt = null;
    protected static $resources = [];
    protected $native = null;

    function __construct() {
        if (is_null(self::$crt)) {
            try {
                self::$crt = new CRT();
            } catch (Exception $e) {
                echo 'Exception while loading CRT: ', $e->getMessage(), "\n";
            }
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
