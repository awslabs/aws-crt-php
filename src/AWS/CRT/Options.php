<?php

namespace AWS\CRT;

final class Options {
    private $options = [];

    public function __construct($opts = []) {
        $this->options = $opts;
    }

    public function __get($name) {
        return (isset($this->options[$name])) ? $this->options[$name] : null;
    }

    public function asArray() {
        return $this->options;
    }

    public function toArray() {
        return array_merge_recursive([], $this->options);
    }

    public function getInt($name) {
        $val = $this->$name;
        return (is_null($val)) ? 0 : (int)$val;
    }

    public function getString($name) {
        $val = (string)$this->$name;
        return (is_null($val)) ? "" : (string)$val;
    }
}
