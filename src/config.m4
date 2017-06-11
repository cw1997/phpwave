dnl $Id$
dnl config.m4 for extension phpwave

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(phpwave, for phpwave support,
dnl Make sure that the comment is aligned:
dnl [  --with-phpwave             Include phpwave support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(phpwave, whether to enable phpwave support,
dnl Make sure that the comment is aligned:
[  --enable-phpwave           Enable phpwave support])

if test "$PHP_PHPWAVE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phpwave -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phpwave.h"  # you most likely want to change this
  dnl if test -r $PHP_PHPWAVE/$SEARCH_FOR; then # path given as parameter
  dnl   PHPWAVE_DIR=$PHP_PHPWAVE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phpwave files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHPWAVE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHPWAVE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phpwave distribution])
  dnl fi

  dnl # --with-phpwave -> add include path
  dnl PHP_ADD_INCLUDE($PHPWAVE_DIR/include)

  dnl # --with-phpwave -> check for lib and symbol presence
  dnl LIBNAME=phpwave # you may want to change this
  dnl LIBSYMBOL=phpwave # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHPWAVE_DIR/$PHP_LIBDIR, PHPWAVE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHPWAVELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phpwave lib version or lib not found])
  dnl ],[
  dnl   -L$PHPWAVE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHPWAVE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phpwave, phpwave.c, $ext_shared)
fi
