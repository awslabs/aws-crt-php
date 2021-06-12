<?php

namespace AWS\CRT\Internal;

use Exception;
use RuntimeException;

/**
 * @internal
 * Forwards calls on to libaws-crt-ffi via FFI
 */
final class FFI {
    private static $ffi = null;
    private static $refcount = 0;

    function __construct() {
        if (is_null(self::$ffi)) {
            try {
                $shlib_ext = 'so';
                $uname_s = php_uname('s');
                if ($uname_s == 'Darwin') {
                    $shlib_ext = 'dylib';
                } else if ($uname_s == 'WINNT') {
                    $shlib_ext = 'dll';
                }
                self::$ffi = \FFI::cdef(
                    file_get_contents(__DIR__ . "/../../../api.h"),
                    __DIR__ . "/../../../libaws-crt-ffi." . $shlib_ext);
                self::init();
            } catch (Exception $e) {
                throw new RuntimeException('Exception while initializing CRT via FFI', 0, $e);
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

    /**
     * Forwards any call made on this object to the FFI function of the
     * same name with the supplied arguments. Argument type hinting and checking
     * occurs at the CRT wrapper.
     */
    function __call(string $name, $args) {
        // Expand strings to (string, length)
        $ffi_args = [];
        foreach ($args as $arg) {
            if (is_string($arg)) {
                $len = strlen($arg);
                $buf = $len ? self::$ffi->new("uint8_t[".$len."]") : null;
                if ($buf) {
                    \FFI::memcpy($buf, $arg, $len);
                }
                $ffi_args []= $buf;
                $ffi_args []= $len;
            } else {
                $ffi_args []= $arg;
            }
        }
        return call_user_func_array(array(self::$ffi, $name), $ffi_args);
    }

    private static function init() {
        return self::$ffi->aws_crt_init();
    }

    private static function clean_up() {
        return self::$ffi->aws_crt_clean_up();
    }
}
