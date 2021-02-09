<?php

require_once('crt.php');

final class EventLoopGroupOptions {
    /**
     * @var int $num_threads - Number of worker threads in the EventLoopGroup. Defaults to 0/1 per logical core.
     */
    public $num_threads = 0;
}

/**
 * Represents 1 or more event loops (1 per thread) for doing I/O and background tasks.
 * Typically, every application has one EventLoopGroup.
 */
final class EventLoopGroup extends NativeResource {
    function __construct($options) {
        parent::__construct();
        $this->acquire(self::$crt->event_loop_group_new($options->num_threads));
    }

    function __destruct() {
        self::$crt->event_loop_group_release($this->native);
        $this->release();
        parent::__destruct();
    }
}
