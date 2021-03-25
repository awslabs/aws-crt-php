<?php

namespace AWS\CRT\HTTP;

use AWS\CRT\IO\InputStream;

class Request extends Message {
    private $body_stream = null;

    public function __construct($method, $path, $query = [], $headers = null, $body_stream = null) {
        parent::__construct($method, $path, $query, $headers);
        if (!is_null($body_stream) && !($body_stream instanceof InputStream)) {
            throw \InvalidArgumentException('body_stream must be an ' . InputStream::class);
        }
        $this->body_stream = $body_stream;
    }

    public static function marshall($request) {
        return parent::marshall($request);
    }

    public static function unmarshall($buf) {
        return parent::_unmarshall($buf, Request::class);
    }

    public function body_stream() {
        return $this->body_stream;
    }
}
