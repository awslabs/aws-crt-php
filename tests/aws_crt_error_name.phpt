--TEST--
aws_crt_error_name
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php
require_once(dirname(__FILE__) . '/common.inc');

echo aws_crt_error_name(0);
?>
--EXPECT--
AWS_ERROR_SUCCESS
