--TEST--
aws_crt_last_error
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php
require_once(dirname(__FILE__) . '/common.inc');

echo aws_crt_last_error();
?>
--EXPECT--
0
