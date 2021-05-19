<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
namespace AWS\CRT\Auth;

use AWS\CRT\NativeResource;

class SigningResult extends NativeResource {
    protected function __construct($native) {
        parent::__construct();

        $this->acquire($native);
    }

    public static function fromNative($ptr) {
        return new SigningResult($ptr);
    }

    public function applyToHttpRequest($http_request) {

    }
}