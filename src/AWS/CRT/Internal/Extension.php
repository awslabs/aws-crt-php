<?php

namespace AWS\CRT\Internal;

use \RuntimeException;

/**
 * Forwards calls on to awscrt PHP extension functions
 */
final class Extension {
    function __construct() {
        if (!extension_loaded('awscrt')) {
            throw new RuntimeException('awscrt extension is not loaded');
        }
    }

    function __call(string $name, $args) {
        return call_user_func_array($name, $args);
    }
}
