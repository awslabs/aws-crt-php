<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\Auth\SigningConfigAWS as SigningConfigAWS;
use AWS\CRT\Auth\Signable as Signable;
use AWS\CRT\HTTP\Request as Request;

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

    public function testSignableFromHttpRequestLifetime() {
        $request = new Request('GET', '/');
        $signable = Signable::fromHttpRequest($request);
        $this->assertNotNull($signable, "Failed to create Signable from HTTP::Request");
        $signable = null;
    }

    public function testSignableFromChunkLifetime() {
        $chunk = "THIS IS A TEST CHUNK IT CONTAINS MULTITUDES";
        $stream = fopen("php://memory", 'r+');
        fputs($stream, $chunk);
        rewind($stream);
        $signable = Signable::fromChunk($stream);
        $this->assertNotNull($signable, "Failed to create Signable from chunk stream");
        $signable = null;
    }

    public function testSignableFromCanonicalRequestLifetime() {
        $canonical_request = "THIS IS A CANONICAL_REQUEST. IT IS DEEPLY CANONICAL";
        $signable = Signable::fromCanonicalRequest($canonical_request);
        $this->assertNotNull($signable, "Failed to create Signable from canonical request");
        $signable = null;
    }
}
