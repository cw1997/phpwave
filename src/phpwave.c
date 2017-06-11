/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
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
#include "php_phpwave.h"

#include <stdio.h>
#include "./wave/wave.h"

/* If you declare any globals in php_phpwave.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(phpwave)
*/

/* True global resources - no need for thread safety here */
static int le_phpwave;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phpwave.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_phpwave_globals, phpwave_globals)
    STD_PHP_INI_ENTRY("phpwave.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_phpwave_globals, phpwave_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_phpwave_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_phpwave_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "phpwave", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto array phpwave(string file_path)
    */
PHP_FUNCTION(phpwave)
{
	char *file_path = NULL;
	int argc = ZEND_NUM_ARGS();
	int file_path_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "s", &file_path, &file_path_len) == FAILURE)
		return;

	if (file_path_len == 0)
	{
		php_printf("%s", "Thank you for using phpwave. code by changwei, at 2017-06-11 18:24:14.");
	}

	// start
	FILE *fp = NULL;

    fp = fopen(file_path, "rb");
    if (!fp) {
        php_error(E_WARNING, ": can't open audio file");
    }

    Wav wav;
    int read_result = fread(&wav, 1, sizeof(wav), fp);
    fclose(fp);

    if (read_result == 0)
    {
    	php_error(E_WARNING, ": read audio file error");
    }

    RIFF_t riff = wav.riff;
    FMT_t fmt = wav.fmt;
    Data_t data = wav.data;

    zval *return_arr;
    ALLOC_INIT_ZVAL(return_arr);
	array_init(return_arr);
	// add_assoc_long(zval *aval, char *key, long lval);
	// add_assoc_zval(zval *aval, char *key, zval *value);

	zval *riff_array;
	ALLOC_INIT_ZVAL(riff_array);
	array_init(riff_array);
	add_assoc_stringl(riff_array, "ChunkID", riff.ChunkID, 4, 1);
	add_assoc_long(riff_array, "ChunkSize", riff.ChunkSize);
	add_assoc_stringl(riff_array, "Format", riff.Format, 4, 1);
	add_assoc_zval(return_arr, "RIFF", riff_array);

	zval *fmt_array;
	ALLOC_INIT_ZVAL(fmt_array);
	array_init(fmt_array);
	add_assoc_stringl(fmt_array, "ChunkID", fmt.Subchunk1ID, 4, 1);
	add_assoc_long(fmt_array, "Subchunk1Size", fmt.Subchunk1Size);
	add_assoc_long(fmt_array, "AudioFormat", fmt.AudioFormat);
	add_assoc_long(fmt_array, "NumChannels", fmt.NumChannels);
	add_assoc_long(fmt_array, "SampleRate", fmt.SampleRate);
	add_assoc_long(fmt_array, "ByteRate", fmt.ByteRate);
	add_assoc_long(fmt_array, "BlockAlign", fmt.BlockAlign);
	add_assoc_long(fmt_array, "BitsPerSample", fmt.BitsPerSample);
	add_assoc_zval(return_arr, "FMT", fmt_array);

	zval *data_array;
	ALLOC_INIT_ZVAL(data_array);
	array_init(data_array);
	add_assoc_stringl(fmt_array, "Subchunk2ID", data.Subchunk2ID, 4, 1);
	add_assoc_long(fmt_array, "Subchunk2Size", data.Subchunk2Size);
	add_assoc_zval(return_arr, "Data", data_array);

	add_assoc_long(return_arr, "duration", data.Subchunk2Size / fmt.ByteRate);

	RETVAL_ZVAL(return_arr, 1, 1);
	// RETURN_TRUE;
	// RETVAL_ZVAL(return_value, copy, dtor)
	//end

	// php_error(E_WARNING, "phpwave: not yet implemented");
}
/* }}} */


/* {{{ php_phpwave_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_phpwave_init_globals(zend_phpwave_globals *phpwave_globals)
{
	phpwave_globals->global_value = 0;
	phpwave_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(phpwave)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(phpwave)
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
PHP_RINIT_FUNCTION(phpwave)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(phpwave)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(phpwave)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "phpwave support", "enabled");
    php_info_print_table_row(2, "version", PHP_PHPWAVE_VERSION);
    php_info_print_table_row(2, "description", "this is a php extension for getting wave audio file's metainfo.");
    php_info_print_table_row(2, "author", "changwei[867597730@qq.com]", "https://github.com/cw1997");
    php_info_print_table_row(2, "datetime", "2017-06-11 18:24:14");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ phpwave_functions[]
 *
 * Every user visible function must have an entry in phpwave_functions[].
 */
const zend_function_entry phpwave_functions[] = {
	PHP_FE(confirm_phpwave_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(phpwave,	NULL)
	PHP_FE_END	/* Must be the last line in phpwave_functions[] */
};
/* }}} */

/* {{{ phpwave_module_entry
 */
zend_module_entry phpwave_module_entry = {
	STANDARD_MODULE_HEADER,
	"phpwave",
	phpwave_functions,
	PHP_MINIT(phpwave),
	PHP_MSHUTDOWN(phpwave),
	PHP_RINIT(phpwave),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(phpwave),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(phpwave),
	PHP_PHPWAVE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHPWAVE
ZEND_GET_MODULE(phpwave)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
