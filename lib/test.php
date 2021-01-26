<?php
require_once('crt.php');

$crt = new CRT();
$crt->init();
var_dump($crt->error_name(0));
$crt->clean_up();
?>
