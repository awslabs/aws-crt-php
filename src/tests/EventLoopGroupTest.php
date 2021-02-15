<?php

final class EventLoopGroupTest extends PHPUnit_Framework_TestCase {

    public function testLifetime() {
        $elg = new EventLoopGroup();
        $elg = null;
    }

    public function testConstructionWithOptions() {
        $options = EventLoopGroup::defaults();
        $options['num_threads'] = 1;
        $elg = new EventLoopGroup($options);
        $elg = null;
    }
}
