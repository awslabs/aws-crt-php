<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\Auth\SigningConfigAWS as SigningConfigAWS;

require_once('common.inc');

final class SigningTest extends CrtTestCase {

    public function testConfigAWSLifetime() {
        $config = new SigningConfigAWS();
        $this->assertNotNull($config, "Failed to create default SigningConfigAWS");
        $config = null;
    }

    public function testConfigAWSConstructionWithOptions() {
        $options = SigningConfigAWS::defaults();
        $options['service'] = 'CRT';
        $options['region'] = 'CRT';
        $config = new SigningConfigAWS($options);
        $this->assertNotNull($config, "Failed to create SigningConfigAWS with custom options");
        $config = null;
    }
}
