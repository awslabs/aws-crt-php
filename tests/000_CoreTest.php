<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\CRT;

require_once('common.inc');

final class CoreTest extends CrtTestCase {

    public function testIsAvailable() {
        $this->assertTrue(CRT::isAvailable());
    }
}