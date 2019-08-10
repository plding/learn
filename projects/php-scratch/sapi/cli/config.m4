dnl config.m4 for sapi cli

PHP_ARG_ENABLE(cli,,
[  --disable-cli           Disable building CLI version of PHP
                           (this forces --without-pear)], yes, no)

AC_MSG_CHECKING(for CLI build)
if test "$PHP_CLI" != "no"; then
  PHP_ADD_MAKEFILE_FRAGMENT($abs_srcdir/sapi/cli/Makefile.frag)

  dnl Set filename
  SAPI_CLI_PATH=sapi/cli/php

  dnl Select SAPI
  PHP_SELECT_SAPI(cli, program, php_cli.c, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1, '$(SAPI_CLI_PATH)')

  BUILD_CLI="\$(LIBTOOL) --mode=link \$(CC) \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) \$(PHP_RPATHS) \$(PHP_GLOBAL_OBJS) \$(PHP_BINARY_OBJS) \$(PHP_CLI_OBJS) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_CLI_PATH)"

  dnl Expose to Makefile
  PHP_SUBST(SAPI_CLI_PATH)
  PHP_SUBST(BUILD_CLI)

  PHP_OUTPUT(sapi/cli/php.1)
fi
AC_MSG_RESULT($PHP_CLI)
