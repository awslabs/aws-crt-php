<?php

namespace AWS\CRT\Auth;

use AWS\CRT\NativeResource as NativeResource;

/**
 * Base class for credentials providers
 */
abstract class CredentialsProvider extends NativeResource {

    function __construct(array $options = []) {
        parent::__construct();
    }

    function __destruct() {
        self::$crt->aws_credentials_provider_release($this->release());
        parent::__destruct();
    }
}
