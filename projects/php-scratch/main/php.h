#ifndef PHP_H
#define PHP_H

#define PHP_API_VERSION 20190809

#ifdef PHP_WIN32
#   ifdef PHP_EXPORTS
#       define PHPAPI __declspec(dllexport)
#   else
#       define PHPAPI __declspec(dllimport)
#   endif
#else
#   if defined(__GNUC__) && __GNUC__ >= 4
#       define PHPAPI __attribute__ ((visibility("default")))
#   else
#       define PHPAPI
#   endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>

#include "zend.h"

#endif /* PHP_H */
