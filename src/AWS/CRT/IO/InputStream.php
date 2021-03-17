<?php

namespace AWS\CRT\IO;

use AWS\CRT\NativeResource as NativeResource;

final class InputStream extends NativeResource {
    private $stream = null;

    public function __construct($stream) {
        $this->stream = $stream;
        $options = self::$crt->aws_input_stream_options_new();
        // The stream implementation in native just converts the PHP stream into
        // a native php_stream* and execute operations entirely in native
        self::$crt->aws_input_stream_options_set_user_data($options, $stream);
        $this->acquire(self::$crt->aws_input_stream_new($options));
        self::$crt->aws_input_stream_options_release($options);
    }

    public function __destruct() {
        self::$crt->aws_input_stream_release($this->release());
        parent::__destruct();
    }

}
