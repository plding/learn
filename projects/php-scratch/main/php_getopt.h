#ifndef PHP_GETOPT_H
#define PHP_GETOPT_H

#include "php.h"

/* Define structure for one recognized option (both single char and long name).
 * If short_open is '-' this is the last option. */
typedef struct _opt_struct {
    char opt_char;
    int need_param;
    char *opt_name;
} opt_struct;

BEGIN_EXTERN_C()
/* holds the index of the latest fetched element from the opts array */
PHPAPI extern int php_optidx;
PHPAPI int php_getopt(int argc, char *const *argv, const opt_struct opts[], char **optarg,
                      int *optind, int show_err, int arg_start);
END_EXTERN_C()

#endif /* PHP_GETOPT_H */
