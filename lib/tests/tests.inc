<?php

// Ensure any version of PHPUnit works, since phpunit5 is the last one that
// works with PHP5.6
if (!class_exists('PHPUnit_Framework_TestCase') &&
  class_exists('\\PHPUnit\\Framework\\TestCase')) {
    abstract class PHPUnit_Framework_TestCase extends \PHPUnit\Framework\TestCase {
    }
}
