/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include "php_aws_crt.h"

PHP_FUNCTION(aws_crt_sha1_new) {
    aws_crt_hash *hash = aws_crt_sha1_new();
    RETURN_LONG((zend_ulong)hash);
}

PHP_FUNCTION(aws_crt_sha256_new) {
    aws_crt_hash *hash = aws_crt_sha256_new();
    RETURN_LONG((zend_ulong)hash);
}

PHP_FUNCTION(aws_crt_md5_new) {
    aws_crt_hash *hash = aws_crt_md5_new();
    RETURN_LONG((zend_ulong)hash);
}

PHP_FUNCTION(aws_crt_hash_update) {
    zend_ulong php_hash = 0;
    const char *buffer = NULL;
    size_t len = 0;
    aws_php_parse_parameters("ls", &php_hash, &buffer, &len);
    aws_crt_hash *hash = (void *)php_hash;
    RETURN_LONG((zend_ulong)aws_crt_hash_update(hash, (uint8_t *)buffer, (uint32_t)len));
}

PHP_FUNCTION(aws_crt_hash_digest) {
    zend_ulong php_hash = 0;
    size_t truncate_to = 0;
    size_t length = 0;
    aws_php_parse_parameters("lll", &php_hash, &truncate_to, &length);
    aws_crt_hash *hash = (void *)php_hash;
    if (truncate_to != 0 && length > truncate_to) {
        length = truncate_to;
    }
    uint8_t *output = aws_crt_hash_digest(hash, truncate_to);
    zval *php_output = NULL;
    ZVAL_PSTRINGL(php_output, (const char *)output, length);
    aws_mem_release(aws_crt_default_allocator(), output);
    // copy false, destroy false?
    RETURN_ZVAL(php_output, false, false);
}

PHP_FUNCTION(aws_crt_hash_destroy) {
    zend_ulong php_hash = 0;
    aws_php_parse_parameters("l", &php_hash);
    aws_crt_hash *hash = (void *)php_hash;
    aws_crt_hash_destroy(hash);
}