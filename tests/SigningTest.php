<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

use AWS\CRT\Auth\SignatureType;
use AWS\CRT\Auth\SigningAlgorithm;
use AWS\CRT\Auth\SigningConfigAWS;
use AWS\CRT\Auth\Signing;
use AWS\CRT\Auth\Signable;
use AWS\CRT\Auth\StaticCredentialsProvider;
use AWS\CRT\HTTP\Request;

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

    const SIGV4TEST_ACCESS_KEY_ID = 'AKIDEXAMPLE';
    const SIGV4TEST_SECRET_ACCESS_KEY = 'wJalrXUtnFEMI/K7MDENG+bPxRfiCYEXAMPLEKEY';
    const SIGV4TEST_SESSION_TOKEN = null;
    const SIGV4TEST_SERVICE = 'service';
    const SIGV4TEST_REGION = 'us-east-1';
    public function testSigv4HeaderSigning() {
        $this->markTestSkipped('WIP');
        $date = mktime(12, 36, 0, 8, 30, 2015);
        $credentials_provider = new StaticCredentialsProvider([
            'access_key_id' => self::SIGV4TEST_ACCESS_KEY_ID,
            'secret_access_key' => self::SIGV4TEST_SECRET_ACCESS_KEY,
            'session_token' => self::SIGV4TEST_SESSION_TOKEN,
        ]);
        $signing_config = new SigningConfigAWS([
            'algorithm' => SigningAlgorithm::SIGv4,
            'signature_type' => SignatureType::HTTP_REQUEST_HEADERS,
            'credentials_provider' => $credentials_provider,
            'region' => self::SIGV4TEST_REGION,
            'service' => self::SIGV4TEST_SERVICE,
        ]);
        $http_request = new Request('GET', '/', [], ['Host' => 'example.amazonaws.com']);
        $this->assertNotNull($http_request, "Unable to create HttpRequest for signing");
        $signable = Signable::fromHttpRequest($http_request);
        $this->assertNotNull($signable, "Unable to create signable from HttpRequest");

        Signing::signRequestAws($signable, $signing_config, function() {

        });
    }
}