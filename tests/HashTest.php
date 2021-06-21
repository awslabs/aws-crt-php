<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\CRT;
use AWS\CRT\Cal\Hash;

require_once('common.inc');

final class HashTest extends CrtTestCase {

    public function testSha256Empty() {
        $h = Hash::sha256_new();
        $digest = $h->digest(0);
        $expected = '\xe3\xb0\xc4\x42\x98\xfc\x1c\x14\x9a\xfb\xf4\xc8\x99\x6f\xb9\x24\x27\xae\x41\xe4\x64\x9b\x93\x4c\xa4\x95\x99\x1b\x78\x52\xb8\x55';
        // $expected = 'test2';
        $this->assertEquals($expected, $digest);
    }
}