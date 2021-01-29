<?php
require_once('preload.php');

final class CRT {
    private static $ffi = null;
    function __construct() {
        if (is_null(self::$ffi)) {
            //$cwd = getcwd();
            //chdir(dirname(__FILE__));
            try {
                self::$ffi = FFI::load(__DIR__ . "/crt.h");
            } catch (Exception $e) {
                echo 'Exception: ', $e->getMessage(), "\n";
            }
            //chdir($cwd);
        }
    }

    function init() {
        return self::$ffi->aws_crt_init();
    }

    function clean_up() {
        return self::$ffi->aws_crt_clean_up();
    }

    function last_error() {
        return self::$ffi->aws_crt_last_error();
    }

    function error_str($error) {
        return self::$ffi->aws_crt_error_str((int)$error);
    }

    function error_name($error) {
        return self::$ffi->aws_crt_error_name((int)$error);
    }
}
