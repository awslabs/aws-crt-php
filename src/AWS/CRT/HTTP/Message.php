<?php

namespace AWS\CRT\HTTP;

use AWS\CRT\NativeResource;

use AWS\CRT\Internal\Encoding;

abstract class Message extends NativeResource {
    private $method = "GET";
    private $path = "";
    private $query = [];
    private $headers = [];

    public function __construct($method, $path, $query = [], $headers = null) {
        $this->method = $method;
        $this->path = $path;
        $this->query = $query;
        $this->headers = !is_null($headers) ? $headers : new Headers();
        $this->acquire(self::$crt->http_message_new_from_blob(self::marshall($this)));
    }

    public function __destruct() {
        self::$crt->http_message_release($this->release());
        parent::__destruct();
    }

    protected static function marshall($msg) {
        $buf = "";
        $buf .= Encoding::encodeString($msg->method);
        $buf .= Encoding::encodeString($msg->pathAndQuery());
        $buf .= Headers::marshall($msg->headers);
        return $buf;
    }

    protected static function _unmarshall($buf, $class=Message::class) {
        $method = Encoding::decodeString($buf);
        $path_and_query = Encoding::decodeString($buf);
        list($path, $query) = split($path_and_query, "?", 2);
        $headers = Headers::unmarshall($buf);

        // Turn query params back into a dictionary
        if (strlen($query)) {
            $query = preg_split("&", $query);
            $query = array_reduce($query, function($params, $pair) {
                list($param, $value) = preg_split( "=", $pair, 2);
                $params[$param] = $value;
                return $params;
            }, $query, []);
        } else {
            $query = [];
        }

        return new $class($method, $path, $query, $headers);
    }

    public function pathAndQuery() {
        $path = $this->path;
        $queries = [];
        foreach ($this->query as $param => $value) {
            $queries []= urlencode($param) . "=" . urlencode($value);
        }
        $query = join("&", $queries);
        if (strlen($query)) {
            $path = join("?", [$path, $query]);
        }
        return $path;
    }

    public function method() {
        return $this->method;
    }

    public function path() {
        return $this->path;
    }

    public function query() {
        return $this->query;
    }

    public function headers() {
        return $this->headers;
    }
}
