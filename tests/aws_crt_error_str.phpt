--TEST--
aws_crt_error_str
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php
require_once(dirname(__FILE__) . '/common.inc');

echo aws_crt_error_str(0);
?>
--EXPECT--
Success.
