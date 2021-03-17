<?php

namespace AWS\CRT\HTTP;

abstract class Message {
    private $path = "";
    private $query = [];
    private $headers = [];

    public function __construct($path, $query = [], $headers = []) {
        $this->path = $path;
        $this->query = $query;
        $this->headers = $headers;
    }
}

class Request extends Message {
    private $body_stream = null;

    public function __construct($path, $query = [], $headers = [], $body_stream = null) {
        parent::__construct($path, $query, $headers);
        $this->body_stream = $body_stream;
    }
}

class Response extends Message {
    private $status_code;

    public function __construct($path, $headers, $status_code) {
        parent::__construct($path, [], $headers);
        $this->status_code = $status_code;
    }
}
