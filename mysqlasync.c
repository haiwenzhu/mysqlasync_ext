/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mysqlasync.h"
#include "ext/mysqlnd/mysqlnd.h"
#include "ext/mysqli/mysqli_mysqlnd.h"
#include "ext/mysqli/php_mysqli_structs.h"

/* If you declare any globals in php_mysqlasync.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mysqlasync)
*/

/* True global resources - no need for thread safety here */
static int le_mysqlasync;

/* {{{ mysqlasync_functions[]
 *
 * Every user visible function must have an entry in mysqlasync_functions[].
 */
const zend_function_entry mysqlasync_functions[] = {
	PHP_FE(mysql_async_get_socket,	NULL)
	PHP_FE_END	/* Must be the last line in mysqlasync_functions[] */
};
/* }}} */

/* {{{ mysqlasync_module_entry
 */
zend_module_entry mysqlasync_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"mysqlasync",
	mysqlasync_functions,
	PHP_MINIT(mysqlasync),
	PHP_MSHUTDOWN(mysqlasync),
	PHP_RINIT(mysqlasync),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mysqlasync),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mysqlasync),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_MYSQLASYNC_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYSQLASYNC
ZEND_GET_MODULE(mysqlasync)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mysqlasync.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mysqlasync_globals, mysqlasync_globals)
    STD_PHP_INI_ENTRY("mysqlasync.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mysqlasync_globals, mysqlasync_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_mysqlasync_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_mysqlasync_init_globals(zend_mysqlasync_globals *mysqlasync_globals)
{
	mysqlasync_globals->global_value = 0;
	mysqlasync_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mysqlasync)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mysqlasync)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(mysqlasync)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mysqlasync)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mysqlasync)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mysqlasync support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
PHP_FUNCTION(mysql_async_get_socket)
{
	MY_MYSQL *mysql;
	zval *mysql_link;
    int fd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &mysql_link) == FAILURE) {
		return;
	}
    
	MYSQLI_FETCH_RESOURCE_CONN(mysql, &mysql_link, MYSQLI_STATUS_VALID);
    php_stream *stream = mysql->mysql->data->net->data->stream;
    if (stream != NULL && SUCCESS == php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void*)&fd, 1) && fd >= 0) {
        RETURN_LONG(fd);
    } else {
        RETURN_FALSE;
    }
}
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
