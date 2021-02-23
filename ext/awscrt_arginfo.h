/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a629a07df494f8ae6563949b2819c833e9d73f9a */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_last_error, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_error_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, error_code, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_error_str arginfo_aws_crt_error_name

#define arginfo_aws_crt_error_debug_str arginfo_aws_crt_error_name


ZEND_FUNCTION(aws_crt_last_error);
ZEND_FUNCTION(aws_crt_error_name);
ZEND_FUNCTION(aws_crt_error_str);
ZEND_FUNCTION(aws_crt_error_debug_str);


static const zend_function_entry ext_functions[] = {
	PHP_FE(aws_crt_last_error, arginfo_aws_crt_last_error)
	PHP_FE(aws_crt_error_name, arginfo_aws_crt_error_name)
	PHP_FE(aws_crt_error_str, arginfo_aws_crt_error_str)
	PHP_FE(aws_crt_error_debug_str, arginfo_aws_crt_error_debug_str)
	PHP_FE_END
};
