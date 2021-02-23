--TEST--
aws_crt_error_debug_str
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php
require_once(dirname(__FILE__) . '/common.inc');

echo aws_crt_error_debug_str(0);
?>
--EXPECT--
aws-c-common: AWS_ERROR_SUCCESS, Success.
