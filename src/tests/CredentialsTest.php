<?php

use AWS\CRT\Auth\AwsCredentials as AwsCredentials;

final class CredentialsTest extends PHPUnit_Framework_TestCase {

    public function testLifetime() {
        $creds = new AwsCredentials(AwsCredentials::defaults());
        $this->assertNotNull($creds, "Failed to create default/empty credentials");
        $creds = null;
    }

    public function testConstructionWithOptions() {
        $options = AwsCredentials::defaults();
        $options['AWS_ACCESS_KEY_ID'] = 'TESTAWSACCESSKEYID';
        $options['AWS_SECRET_ACCESS_KEY'] = 'TESTSECRETaccesskeyThatDefinitelyDoesntWork';
        $options['AWS_SESSION_TOKEN'] = 'ThisIsMyTestSessionTokenIMadeItUpMyself';
        $creds = new AwsCredentials($options);
        $this->assertNotNull($creds, "Failed to create Credentials with options");
        $creds = null;
    }
}
