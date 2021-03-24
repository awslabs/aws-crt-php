<?php

namespace AWS\CRT\HTTP;

class Response extends Message {
    private $status_code;

    public function __construct($method, $path, $query, $headers, $status_code) {
        parent::__construct($method, $path, $query, $headers);
        $this->status_code = $status_code;
    }

    public static function marshall($response) {
        return parent::marshall($response);
    }

    public static function unmarshall($buf) {
        return parent::_unmarshall($buf, Response::class);
    }
}
