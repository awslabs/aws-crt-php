<?php

namespace AWS\CRT\IO;

use AWS\CRT\NativeResource as NativeResource;
use AWS\CRT\Options as Options;

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
            'max_threads' => 0,
        );
    }

    function __construct(array $options = []) {
        parent::__construct();
        if (count($options) == 0) {
            $options = self::defaults();
        }
        $options = new Options($options);
        $elg_options = self::$crt->event_loop_group_options_new();
        self::$crt->event_loop_group_options_set_max_threads($elg_options, $options->getInt('max_threads'));
        $this->acquire(self::$crt->event_loop_group_new($elg_options));
        self::$crt->event_loop_group_options_release($elg_options);
    }

    function __destruct() {
        self::$crt->event_loop_group_release($this->release());
        parent::__destruct();
    }
}
