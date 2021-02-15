<?php

namespace AWS\CRT\IO;

use AWS\CRT\NativeResource as NativeResource;

/**
 * Represents 1 or more event loops (1 per thread) for doing I/O and background tasks.
 * Typically, every application has one EventLoopGroup.
 *
 * @param array options:
 * - int num_threads - Number of worker threads in the EventLoopGroup. Defaults to 0/1 per logical core.
 */
final class EventLoopGroup extends NativeResource {

    static function defaults() {
        return array(
            'num_threads' => 0,
        );
    }

    function __construct(array $options = array()) {
        parent::__construct();
        if (count($options) == 0) {
            $options = self::defaults();
        }
        $this->acquire(self::$crt->event_loop_group_new($options['num_threads']));
    }

    function __destruct() {
        self::$crt->event_loop_group_release($this->native);
        $this->release();
        parent::__destruct();
    }
}
