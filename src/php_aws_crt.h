
#ifndef PHP_AWS_CRT_H
#define PHP_AWS_CRT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

ZEND_BEGIN_MODULE_GLOBALS(awscrt)
int log_level;
ZEND_END_MODULE_GLOBALS(awscrt)

ZEND_EXTERN_MODULE_GLOBALS(awscrt)

#define AWSCRT_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(awscrt, v)

#endif /* PHP_AWS_CRT_H */
