<?php

require_once('crt.php');

final class EventLoopGroupOptions {
    public $num_threads = 0;
}

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
