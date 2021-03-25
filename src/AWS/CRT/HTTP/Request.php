<?php

namespace AWS\CRT\HTTP;

class Request extends Message {
    private $body_stream = null;

    public function __construct($method, $path, $query = [], $headers = null, $body_stream = null) {
        parent::__construct($method, $path, $query, $headers);
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
