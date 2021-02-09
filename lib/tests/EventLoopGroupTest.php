<?php

require_once('tests.inc');

final class EventLoopGroupTest extends PHPUnit_Framework_TestCase {

    public function testLifetime() {
        $elg = new EventLoopGroup(new EventLoopGroupOptions());
        $elg = null;
    }

    public function testConstructionWithOptions() {
        $options = new EventLoopGroupOptions();
        $options->num_threads = 1;
        $elg = new EventLoopGroup($options);
        $elg = null;
    }
}
