<?php

namespace AWS\CRT;

use AWS\CRT\Internal\Extension;
use AWS\CRT\Internal\FFI;

use \RuntimeException;

/**
 * Wrapper for the interface to the CRT. There only ever needs to be one of these, but
 * additional instances won't cost anything other than their memory.
 * Creating an instance of any NativeResource will activate the CRT binding. User code
 * should only need to create one of these if they are only accessing CRT:: static functions.
 */
final class CRT {

    private static $impl = null;
    private static $refcount = 0;

    function __construct() {
        if (is_null(self::$impl)) {
            $backends = ['Extension', 'FFI'];
            if (getenv('AWS_CRT_PHP_EXTENSION')) {
                $backends = ['Extension'];
            } else if (getenv('AWS_CRT_PHP_FFI')) {
                $backends = ['FFI'];
            }
            $exceptions = [];
            foreach ($backends as $backend) {
                try {
                    $backend = 'AWS\\CRT\\Internal\\' . $backend;
                    self::$impl = new $backend();
                } catch (RuntimeException $rex) {
                    array_push($exceptions, $rex);
                }
            }
            if (is_null(self::$impl)) {
                throw new RuntimeException('Unable to initialize AWS CRT via ' . join(', ', $backends) . ": \n" . join("\n", $exceptions), -1);
            }
        }
        ++self::$refcount;
    }

    function __destruct() {
        if (--self::$refcount == 0) {
            self::$impl = null;
        }
    }

    /**
     * @return integer last error code reported within the CRT
     */
    public static function last_error(): int {
        return self::$impl->aws_crt_last_error();
    }

    /**
     * @param integer $error Error code from the CRT, usually delivered via callback or {@see last_error}
     * @return string Human-readable description of the provided error code
     */
    public static function error_str(int $error) : string {
        return self::$impl->aws_crt_error_str((int) $error);
    }

    /**
     * @param integer $error Error code from the CRT, usually delivered via callback or {@see last_error}
     * @return string Name/enum identifier for the provided error code
     */
    public static function error_name(int $error) : string {
        return self::$impl->aws_crt_error_name((int) $error);
    }

    /**
     * @return object Pointer to native event_loop_group_options
     */
    function event_loop_group_options_new() {
        return self::$impl->aws_crt_event_loop_group_options_new();
    }

    /**
     * @param object $elg_options Pointer to native event_loop_group_options
     */
    function event_loop_group_options_release($elg_options) {
        self::$impl->aws_crt_event_loop_group_options_release($elg_options);
    }

    /**
     * @param object $elg_options Pointer to native event_loop_group_options
     * @param integer $max_threads Maximum number of threads to allow the event loop group to use, default: 0/1 per CPU core
     */
    function event_loop_group_options_set_max_threads($elg_options, int $max_threads) {
        self::$impl->aws_crt_event_loop_group_options_set_max_threads($elg_options, $max_threads);
    }

    /**
     * @param object Pointer to event_loop_group_options, {@see event_loop_group_options_new}
     * @return object Pointer to the new event loop group
     */
    function event_loop_group_new($options) {
        return self::$impl->aws_crt_event_loop_group_new($options);
    }

    /**
     * @param object $elg Pointer to the event loop group to release
     */
    function event_loop_group_release($elg) {
        return self::$impl->aws_crt_event_loop_group_release($elg);
    }
}
