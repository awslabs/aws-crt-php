<?php

use AWS\CRT\IO\EventLoopGroup as EventLoopGroup;

final class EventLoopGroupTest extends PHPUnit_Framework_TestCase {

    public function testLifetime() {
        $elg = new EventLoopGroup();
        $this->assertNotNull($elg, "Failed to create default EventLoopGroup");
        $elg = null;
    }

    public function testConstructionWithOptions() {
        $options = EventLoopGroup::defaults();
        $options['num_threads'] = 1;
        $elg = new EventLoopGroup($options);
        $this->assertNotNull($elg, "Failed to create EventLoopGroup with 1 thread");
        $elg = null;
    }
}
