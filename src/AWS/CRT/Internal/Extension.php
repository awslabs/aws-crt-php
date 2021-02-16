<?php

namespace AWS\CRT\Internal;

use \RuntimeException;

/**
 * @internal
 * Forwards calls on to awscrt PHP extension functions
 */
final class Extension {
    function __construct() {
        if (!extension_loaded('awscrt')) {
            throw new RuntimeException('awscrt extension is not loaded');
        }
    }

    /**
     * Forwards any call made on this object to the extension function of the
     * same name with the supplied arguments. Argument type hinting and checking
     * occurs at the CRT wrapper.
     */
    function __call(string $name, $args) {
        return call_user_func_array($name, $args);
    }
}
