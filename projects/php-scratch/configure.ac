#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([php-scratch], [0.0.1], [77676182@qq.com])

PHP_CONFIG_NICE(config.nice)

AC_CONFIG_HEADERS([main/php_config.h])

# Settings we want to make before the checks.

cwd=`pwd`

php_shtool=$srcdir/build/shtool
T_MD=`$php_shtool echo -n -e %B`
T_ME=`$php_shtool echo -n -e %b`

PHP_INIT_BUILD_SYSTEM

# We want this one before the checks, so the checks can modify CFLAGS.
test -z "$CFLAGS" && auto_cflags=1

abs_srcdir=`(cd $srcdir; pwd)`
abs_builddir=`pwd`

php_abs_top_srcdir=$abs_srcdir
php_abs_top_builddir=$abs_builddir

# Because ``make install'' is often performed by the superuser,
# we create the libs subdirectory as the user who configures PHP.
# Otherwise, the current user will not be able to delete libs
# or the contents of libs.

$php_shtool mkdir -p libs
rm -f libs/*

# Checks for programs.
AC_PROG_CC([cc gcc])
# PHP_DETECT_ICC
# PHP_DETECT_SUNCC
# AC_PROG_CC_C_O
# # Change to AC_PROG_CC_STDC when we start requiring a post-2.13 autoconf
# # AC_PROG_CC_STDC
# AC_PROG_CPP
# AC_USE_SYSTEM_EXTENSIONS
# AC_PROG_LN_S

# # Checks for some support/generator progs
# PHP_PROG_AWK
# PHP_PROG_BISON
# PHP_PROG_RE2C

# Checks for libraries.

PHP_HELP_SEPARATOR([SAPI modules:])

# SAPI configuration.
# -------------------------------------------------------------------------

PHP_CONFIGURE_PART(Configuring SAPI modules)

esyscmd(./build/config-stubs sapi)

# Show which main SAPI was selected
AC_MSG_CHECKING([for chosen SAPI module])
AC_MSG_RESULT([$PHP_SAPI])

# Show which binaries were selected
AC_MSG_CHECKING([for executable SAPI binaries])
if test "$PHP_BINARIES"; then
  AC_MSG_RESULT([$PHP_BINARIES])
else
  AC_MSG_RESULT([none])
fi

# # Checks for header files.
# AC_CHECK_HEADERS([malloc.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# AC_PROG_LIBTOOL

INCLUDES="$INCLUDES -I\$(top_builddir)/Zend"

PHP_SUBST(PHP_SAPI_OBJS)
PHP_SUBST(PHP_BINARY_OBJS)
PHP_SUBST(PHP_GLOBAL_OBJS)

PHP_SUBST(PHP_BINARIES)

PHP_SUBST_OLD(INCLUDES)

all_targets="\$(PHP_BINARIES)"

PHP_SUBST(all_targets)

PHP_ADD_SOURCES(main, getopt.c, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

PHP_GEN_GLOBAL_MAKEFILE

AC_OUTPUT
