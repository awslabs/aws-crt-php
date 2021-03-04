--TEST--
aws_crt_event_loop_group
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php
require_once(dirname(__FILE__) . '/common.inc');

$elg = aws_crt_event_loop_group_new(1);
var_dump($elg);
aws_crt_event_loop_group_release($elg);
?>
--EXPECTREGEX--
int\(\d+\)
