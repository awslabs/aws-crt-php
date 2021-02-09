<?php
// php.ini
// ffi.enable=preload
// opcache.preload=preload.php
if (function_exists("opcache_compile_file")) {
    opcache_compile_file(__DIR__ . "/lib.php");
}
