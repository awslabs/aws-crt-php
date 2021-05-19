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

    function __destruct() {
        // No release necessary, SigningResults are transient
        $this->release();
        parent::__destruct();
    }

    public static function fromNative($ptr) {
        return new SigningResult($ptr);
    }

    public function applyToHttpRequest($http_request) {
        self::$crt->signing_result_apply_to_http_request($this->native, $http_request->native);
    }
}