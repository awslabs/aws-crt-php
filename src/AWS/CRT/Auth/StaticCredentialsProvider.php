<?php

namespace AWS\CRT\Auth;

/**
 * Provides a static set of AWS credentials
 *
 * @param array options:
 * - string access_key_id - AWS Access Key Id
 * - string secret_access_key - AWS Secret Access Key
 * - string session_token - Optional STS session token
 */
final class StaticCredentialsProvider extends CredentialsProvider {

    static function defaults() {
        return array(
            'access_key_id' => '',
            'secret_access_key' => '',
            'session_token' => '',
        );
    }

    private $credentials = null;

    public function __get($name) {
        return $this->$name;
    }

    function __construct(array $options = array()) {
        parent::__construct();
        if (count($options) == 0) {
            $options = self::defaults();
        }
        $this->credentials = new AwsCredentials($options);

        $provider_options = self::$crt->aws_credentials_provider_static_options_new();
        self::$crt->aws_credentials_provider_static_options_set_access_key_id($provider_options, $this->credentials->access_key_id);
        self::$crt->aws_credentials_provider_static_options_set_secret_access_key($provider_options, $this->credentials->secret_access_key);
        self::$crt->aws_credentials_provider_static_options_set_session_token($provider_options, $this->credentials->session_token);
        $this->acquire(self::$crt->aws_credentials_provider_static_new($provider_options));
        self::$crt->aws_credentials_provider_static_options_release($provider_options);
    }
}
