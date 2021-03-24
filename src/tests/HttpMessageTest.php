<?php

use AWS\CRT\HTTP\Message;
use AWS\CRT\HTTP\Headers;
use AWS\CRT\HTTP\Request;
use AWS\CRT\HTTP\Response;

require_once('common.inc');

final class HttpMessageTest extends CrtTestCase {
    public function testHeaders() {
        $headers = new Headers();
        $this->assertEquals(0, $headers->count());
    }

    public function testHeadersMarshalling() {
        $headers_array = [
            "host" => "s3.amazonaws.com",
            "test" => "this is a test header value"
        ];
        $headers = new Headers($headers_array);
        $this->assertEquals(2, $headers->count());
        $this->assertEquals($headers_array['host'], $headers->get('host'));
        $this->assertEquals($headers_array['test'], $headers->get('test'));
        $buffer = Headers::marshall($headers);
        $headers_copy = Headers::unmarshall($buffer);
        $this->assertEquals(2, $headers_copy->count());
        $this->assertEquals($headers_array['host'], $headers_copy->get('host'));
        $this->assertEquals($headers_array['test'], $headers_copy->get('test'));
    }

    public function testRequestMarshalling() {
        $headers_array = [
            "host" => "s3.amazonaws.com",
            "test" => "this is a test header value"
        ];
        $headers = new Headers($headers_array);
        $method = "GET";
        $path = "/index.php";
        $query = [];

        $msg = new Request($method, $path, $query, $headers);
        $msg_buf = Request::marshall($msg);
        $msg_copy = Request::unmarshall($msg_buf);

        $this->assertEquals($method, $msg_copy->method());
        $this->assertEquals($path, $msg_copy->path());
        $this->assertEquals($query, $msg_copy->query());
        $this->assertEquals($headers_array, $msg_copy->headers()->toArray());
    }
}
