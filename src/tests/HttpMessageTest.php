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

    private function assertMessagesMatch($a, $b) {
        $this->assertEquals($a->method(), $b->method());
        $this->assertEquals($a->path(), $b->path());
        $this->assertEquals($a->query(), $b->query());
        $this->assertEquals($a->headers()->toArray(), $b->headers()->toArray());
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

        $this->assertMessagesMatch($msg, $msg_copy);
    }

    public function testRequestMarshallingWithQueryParams() {
        $headers_array = [
            "host" => "s3.amazonaws.com",
            "test" => "this is a test header value"
        ];
        $headers = new Headers($headers_array);
        $method = "GET";
        $path = "/index.php";
        $query = [
            'request' => 1,
            'test' => true,
            'answer' => 42,
            'foo' => 'bar',
        ];

        $msg = new Request($method, $path, $query, $headers);
        $msg_buf = Request::marshall($msg);
        $msg_copy = Request::unmarshall($msg_buf);

        $this->assertMessagesMatch($msg, $msg_copy);
    }

    public function testResponseMarshalling() {
        $headers_array = [
            "content-length" => "42",
            "test" => "this is a test header value"
        ];
        $headers = new Headers($headers_array);
        $method = "GET";
        $path = "/index.php";
        $query = [
            'response' => 1
        ];

        $msg = new Response($method, $path, $query, $headers, 400);
        $msg_buf = Request::marshall($msg);
        $msg_copy = Request::unmarshall($msg_buf);

        $this->assertMessagesMatch($msg, $msg_copy);
    }
}