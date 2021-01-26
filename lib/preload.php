<?php
// php.ini
// ffi.enable=preload
// opcache.preload=preload.php
FFI::load(__DIR__ . "/crt.h");
if (function_exists("opcache_compile_file")) {
    opcache_compile_file(__DIR__ . "/crt.php");
}
?>
