<?php

namespace AWS\CRT\Internal;

use \Exception;
use \RuntimeException;

/**
 * @internal
 * Forwards calls on to libaws-crt-ffi via FFI
 */
final class FFI {
    private static $ffi = null;
    private static $refcount = 0;
    private static $NULL = null;

    function __construct() {
        if (is_null(self::$ffi)) {
            try {
                self::$ffi = \FFI::cdef(file_get_contents(__DIR__ . "/../../../api.h"), __DIR__ . "/../../../libaws-crt-ffi.so");
                self::init();
            } catch (Exception $e) {
                throw new RuntimeException('Exception while initializing CRT via FFI', 0, $e);
            }
            self::$NULL = \FFI::cdef("uint8_t*");
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
        $transformed_args = [];
        // process args, convert strings into byte buffers (uint8_t* buffer, size_t length)
        $buffers = [];
        foreach ($args as $arg) {
            if (is_string($arg)) {
                $buf_len = strlen($arg);
                $buf = self::$ffi->new("uint8_t[" . $buf_len . "]");
                \FFI::memcpy($buf, $arg, $buf_len);

                array_push($buffers, $buf);
                array_push($transformed_args, \FFI::cast("uint8_t*", $buf));
                array_push($transformed_args, $buf_len);
            } else {
                array_push($transformed_args, $arg);
            }
        }
        $retval = call_user_func_array(array(self::$ffi, $name), $transformed_args);
        return $retval;
    }

    private static function init() {
        return self::$ffi->aws_crt_init();
    }

    private static function clean_up() {
        return self::$ffi->aws_crt_clean_up();
    }
}
