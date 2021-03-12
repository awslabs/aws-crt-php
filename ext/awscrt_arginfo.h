/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 2df622c03a618da4e83a5bee3e1794a0773c9366 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_last_error, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_error_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, error_code, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_aws_crt_error_str arginfo_aws_crt_error_name

#define arginfo_aws_crt_error_debug_str arginfo_aws_crt_error_name

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_options_new, 0, 0, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_options_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, elg_options, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_options_set_max_threads, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, elg_options, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, max_threads, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_new, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max_threads, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_aws_crt_event_loop_group_release, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, event_loop_group, IS_OBJECT, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(aws_crt_last_error);
ZEND_FUNCTION(aws_crt_error_name);
ZEND_FUNCTION(aws_crt_error_str);
ZEND_FUNCTION(aws_crt_error_debug_str);
ZEND_FUNCTION(aws_crt_event_loop_group_options_new);
ZEND_FUNCTION(aws_crt_event_loop_group_options_release);
ZEND_FUNCTION(aws_crt_event_loop_group_options_set_max_threads);
ZEND_FUNCTION(aws_crt_event_loop_group_new);
ZEND_FUNCTION(aws_crt_event_loop_group_release);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(aws_crt_last_error, arginfo_aws_crt_last_error)
	ZEND_FE(aws_crt_error_name, arginfo_aws_crt_error_name)
	ZEND_FE(aws_crt_error_str, arginfo_aws_crt_error_str)
	ZEND_FE(aws_crt_error_debug_str, arginfo_aws_crt_error_debug_str)
	ZEND_FE(aws_crt_event_loop_group_options_new, arginfo_aws_crt_event_loop_group_options_new)
	ZEND_FE(aws_crt_event_loop_group_options_release, arginfo_aws_crt_event_loop_group_options_release)
	ZEND_FE(aws_crt_event_loop_group_options_set_max_threads, arginfo_aws_crt_event_loop_group_options_set_max_threads)
	ZEND_FE(aws_crt_event_loop_group_new, arginfo_aws_crt_event_loop_group_new)
	ZEND_FE(aws_crt_event_loop_group_release, arginfo_aws_crt_event_loop_group_release)
	ZEND_FE_END
};
