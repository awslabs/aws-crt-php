--TEST--                                 
Version: Simple function call
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php
require_once(dirname(__FILE__) . '/common.inc');

echo awscrt_version();
?>
===DONE===
--EXPECT--
1.0.0-dev
