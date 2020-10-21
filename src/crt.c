
#include "php_aws_crt.h"

ZEND_DECLARE_MODULE_GLOBALS(awscrt);

PHP_INI_BEGIN()
STD_PHP_INI_ENTRY("awscrt.log_level", "", PHP_INI_ALL, OnUpdateString, log_level, zend_awscrt_globals, awscrt_globals)
PHP_INI_END()

static PHP_MINIT_FUNCTION(awscrt)
{
    REGISTER_INI_ENTRIES();
    return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(awscrt)
{
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

static PHP_GINIT_FUNCTION(awscrt)
{
#if defined(COMPILE_DL_ASTKIT) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    awscrt_globals->log_level = 0;
}

zend_module_entry awscrt_module_entry = {
    STANDARD_MODULE_HEADER,
    "awscrt",
    NULL, /* functions */
    PHP_MINIT(awscrt),
    PHP_MSHUTDOWN(awscrt),
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
    NO_VERSION_YET,
    PHP_MODULE_GLOBALS(awscrt),
    PHP_GINIT(awscrt),
    NULL, /* GSHUTDOWN */
    NULL, /* RPOSTSHUTDOWN */
    STANDARD_MODULE_PROPERTIES_EX};

#ifdef COMPILE_DL_AWSCRT
ZEND_GET_MODULE(awscrt)
#endif
