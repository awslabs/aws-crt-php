<?php

/**
 * Wrapper for the FFI interface to the CRT. There only ever needs to be one of these.
 * Creating an instance of any NativeResource will activate the CRT binding. User code
 * should only need to create one of these if they are only accessing CRT:: functions.
 */
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

    private static function init() {
        return self::$ffi->aws_crt_init();
    }

    private static function clean_up() {
        return self::$ffi->aws_crt_clean_up();
    }

    /**
     * @return integer last error code reported within the CRT
     */
    public static function last_error() {
        return self::$ffi->aws_crt_last_error();
    }

    /**
     * @param integer $error Error code from the CRT, usually delivered via callback or {@see last_error}
     * @return string Human-readable description of the provided error code
     */
    public static function error_str($error) {
        return self::$ffi->aws_crt_error_str((int) $error);
    }

    /**
     * @param integer $error Error code from the CRT, usually delivered via callback or {@see last_error}
     * @return string Name/enum identifier for the provided error code
     */
    public static function error_name($error) {
        return self::$ffi->aws_crt_error_name((int) $error);
    }

    function event_loop_group_new($options) {
        return self::$ffi->aws_crt_event_loop_group_new($options->num_threads);
    }

    function event_loop_group_release($elg) {
        return self::$ffi->aws_crt_event_loop_group_release($elg);
    }
}

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
