<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
namespace AWS\CRT\Cal;

use AWS\CRT\NativeResource;

class Hash extends NativeResource {
    private function __construct($hash, $len) {
        parent::__construct();
        $this->hash = $hash;
        $this->len = $len;
    }

    public static function sha1_new() {
        return new Hash(self::$crt->sha1_new(), 20);
    }

    public static function sha256_new() {
        return new Hash(self::$crt->sha256_new(), 32);
    }

    public static function md5_new() {
        return new Hash(self::$crt->md5_new(), 16);
    }

    public function update($buffer) {
        self::$crt->hash_update($this->hash, $buffer);
    }

    public function digest($truncate_to) {
        return self::$crt->hash_digest($this->hash, $truncate_to, $this->len);
    }

    function __destruct() {
        self::$crt->hash_destroy($this->hash);
        parent::__destruct();
    }
}