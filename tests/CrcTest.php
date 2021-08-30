<?php
/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
use AWS\CRT\CRT;

require_once('common.inc');

final class CrcTest extends CrtTestCase {

    // public function testCrc32ZeroesOneShot() {
    //     $input = implode(array_map("chr", array_fill(0, 32, 0)));
    //     $output = CRT::crc32($input);
    //     $expected = 0x190A55AD;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32ZeroesIterated() {
    //     $output = 0;
    //     for ($i = 0; $i < 32; $i++) {
    //         $output = CRT::crc32("\x00", $output);
    //     }
    //     $expected = 0x190A55AD;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32ValuesOneShot() {
    //     $input = implode(array_map("chr", range(0, 31)));
    //     $output = CRT::crc32($input);
    //     $expected = 0x91267E8A;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32ValuesIterated() {
    //     $output = 0;
    //     foreach (range(0, 31) as $n) {
    //         $output = CRT::crc32(chr($n), $output);
    //     }
    //     $expected = 0x91267E8A;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32LargeBuffer() {
    //     $input = implode(array_map("chr", array_fill(0, 1 << 20, 0)));
    //     $output = CRT::crc32($input);
    //     $expected = 0xA738EA1C;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32cZeroesOneShot() {
    //     $input = implode(array_map("chr", array_fill(0, 32, 0)));
    //     $output = CRT::crc32c($input);
    //     $expected = 0x8A9136AA;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32cZeroesIterated() {
    //     $output = 0;
    //     for ($i = 0; $i < 32; $i++) {
    //         $output = CRT::crc32c("\x00", $output);
    //     }
    //     $expected = 0x8A9136AA;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32cValuesOneShot() {
    //     $input = implode(array_map("chr", range(0, 31)));
    //     $output = CRT::crc32c($input);
    //     $expected = 0x46DD794E;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32cValuesIterated() {
    //     $output = 0;
    //     foreach (range(0, 31) as $n) {
    //         $output = CRT::crc32c(chr($n), $output);
    //     }
    //     $expected = 0x46DD794E;
    //     $this->assertEquals($output, $expected);
    // }

    // public function testCrc32cLargeBuffer() {
    //     $input = implode(array_map("chr", array_fill(0, 1 << 20, 0)));
    //     $output = CRT::crc32c($input);
    //     $expected = 0x14298C12;
    //     $this->assertEquals($output, $expected);
    // }

    private function update_summary($count, &$mean, &$M2, &$my_min, &$my_max, $new_value) {
        $delta = $new_value - $mean;
        $mean += $delta / $count;
        $delta2 = $new_value - $mean;
        $M2 += $delta * $delta2;
        $my_min = min($my_min, $new_value);
        $my_max = max($my_max, $new_value);
    }
    
    private function finalize_summary($count, $M2) {
        return $M2 / $count;
    }
    
    private function print_stats($means, $variances, $mins, $maxs, $chunk_sizes){
        $len = count($means);
        for ($i = 0; $i < count($means); $i++){
            echo("chunk size: {$chunk_sizes[$i]}, min: {$mins[$i]}, max: {$maxs[$i]}, mean: {$means[$i]}, variance: {$variances[$i]}\n");
        }
    }
    
    
    private function profile_sequence_chunks($to_hash, $chunk_size, $iterations, $checksum_fn){
        $mean = 0;
        $M2 = 0;
        $min = INF;
        $max = 0;
        for ($x = 0; $x < $iterations; $x++){
            $i = 0;
            $prev = 0;
            $start = microtime(true);
            while($i + $chunk_size < strlen($to_hash)){
                $prev = $checksum_fn(substr($to_hash, $i, $chunk_size), $prev);
                $i = $i + $chunk_size;
            }
            $prev = $checksum_fn(substr($to_hash, $i), $prev);
            $end =  microtime(true);
            $this->update_summary($x + 1, $mean, $M2, $min, $max, ($end - $start) * 1000000000);
        }
        return $mean;
    }
    
    private function profile_sequence($to_hash, $chunk_sizes, $iterations_per_sequence, $checksum_fn) {
        $times = [];
        for($i = 0; $i < count($chunk_sizes); $i++) {
            $this->profile_sequence_chunks($to_hash, $chunk_sizes[$i], $iterations_per_sequence, $checksum_fn);
            array_push($times, $this->profile_sequence_chunks($to_hash, $chunk_sizes[$i], $iterations_per_sequence, $checksum_fn));
        }
        return $times;
    }
    
    private function profile($size, $chunk_sizes, $num_sequences, $iterations_per_sequence, $checksum_fn){
        $means = array_fill(0, count($chunk_sizes), 0);
        $variances = array_fill(0, count($chunk_sizes), 0);
        $mins = array_fill(0, count($chunk_sizes), INF);
        $maxs = array_fill(0, count($chunk_sizes), 0);
        for($x = 0; $x < $num_sequences; $x++){
            $buffer = random_bytes($size);
            $times = $this->profile_sequence($buffer, $chunk_sizes, $iterations_per_sequence, $checksum_fn);
            for($i = 0; $i < count($chunk_sizes); $i++) {
                $stats = $this->update_summary($x + 1, $means[$i], $variances[$i], $mins[$i], $maxs[$i], $times[$i]);
            }
        }
        for ($i = 0; $i < count($variances); $i++){
            $variances[$i] = $this->finalize_summary($num_sequences, $variances[$i]);
        }
        $this->print_stats($means, $variances, $mins, $maxs, $chunk_sizes);
    }

    public function testCrcBenchmark() {
        // $input = implode(array_map("chr", array_fill(0, 1 << 20, 0)));
        // $output = CRT::crc32c($input);
        // $expected = 0x14298C12;
        // $this->assertEquals($output, $expected);

        // echo("\ncrc32\n");
        $chunk_sizes = [1 << 22, 1 << 20, 1 << 10, 1 << 9, 1 << 8, 1 << 7];
        // profile(1 << 22, chunk_sizes, 1000, 1,  CRT::crc32);
        echo("\ncrc32c\n");
        $this->profile(
            1 << 22, 
            $chunk_sizes, 
            10, 
            1, 
            function($in, $prev) {
                CRT::crc32c($in, $prev);
            }
    );
        $this->assertEquals(1, 1);
    }
}
