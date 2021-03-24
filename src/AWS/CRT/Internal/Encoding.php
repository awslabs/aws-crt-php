<?php

namespace AWS\CRT\Internal;

final class Encoding {
    public static function readString(&$buffer) {
        list($str, $len) = self::decodeString($buffer);
        // Advance by sizeof(length) + strlen(str)
        $buffer = substr($buffer, 4 + $len);
        return $str;
    }

    public static function readStrings($buffer) {
        $strings = [];
        while (strlen($buffer)) {
            $strings []= self::readString($buffer);
        }
        return $strings;
    }

    public static function decodeString($buffer) {
        return unpack("N/c*", $buffer);
    }

    public static function encodeString($str) {
        return pack("Nc*", strlen($str), $str);
    }
}
