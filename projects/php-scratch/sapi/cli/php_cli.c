#include "php.h"
#include "php_getopt.h"

const opt_struct OPTIONS[] = {
    {'h', 0, "help"},
    {'?', 0, "usage"},
    {'-', 0, NULL}  /* end of args */
};

/* {{{ php_cli_usage
 */
static void php_cli_usage(char *argv0)
{
    char *prog;

    prog = strrchr(argv0, '/');
    if (prog) {
        prog++;
    } else {
        prog = "php";
    }

    printf("Usage: %s [options] [-f] <file> [--] [args...]\n"
               "   %s options] -r <code> [--] [args...]\n"
               "   %s [options] [-B <begin_code>] -R <code> [-E <end_code>] [--] [args...]\n"
			   "   %s [options] [-B <begin_code>] -F <file> [-E <end_code>] [--] [args...]\n"
			   "   %s [options] -S <addr>:<port> [-t docroot] [router]\n"
			   "   %s [options] -- [args...]\n"
			   "   %s [options] -a\n"
			   "\n"
               , prog, prog, prog, prog, prog, prog, prog);
}
/* }}} */

/* {{{ main
 */
int main(int argc, char **argv)
{
    int c;
    char *php_optarg = NULL;
    int php_optind = 1;

    while ( (c = php_getopt(argc, argv, OPTIONS, &php_optarg, &php_optind, 0, 2)) != -1) {
        switch (c) {
        case 'h': /* help & quit */
        case '?':
            php_cli_usage(argv[0]);
            break;
        default:
            break;
        }
    }

    exit(EXIT_SUCCESS);
}
/* }}} */
