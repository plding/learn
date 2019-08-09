/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2018 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Ding Peilong <77676182@qq.com>                               |
   +----------------------------------------------------------------------+
*/

#include "php.h"
#include "php_ini.h"
#include "php_main.h"
#include "php_globals.h"
#include "php_variables.h"
#include "php_getopt.h"
#include "php_network.h"
#include "zend_hash.h"
#include "zend_modules.h"
#include "zend_interfaces.h"

#include "ext/reflection/php_reflection.h"
#include "ext/standard/php_standard.h"

#include "SAPI.h"
#include "cli.h"

#ifndef PHP_WIN32
# define php_select(m, r, w, e, t)  select(m, r, w, e, t)
#endif

const opt_struct OPTIONS[] = {
    {'a', 0, "interactive"},
    {'h', 0, "help"},
    {'i', 0, "info"},
    {'m', 0, "modules"},
    {'v', 0, "version"},
    {'?', 0, "usage"},
    {'-', 0, NULL} /* end of args */
};

static int print_module_info(zval *element) /* {{{ */
{
    zend_module_entry *module = (zend_module_entry *) Z_PTR_P(element);
    php_printf("%s\n", module->name);
    return ZEND_HASH_APPLY_KEEP;
}
/* }}} */

static int module_name_cmp(const void *a, const void *b) /* {{{ */
{
    Bucket *f = (Bucket *) a;
    Bucket *s = (Bucket *) b;

    return strcasecmp(((zend_module_entry *) Z_PTR(f->val))->name,
                      ((zend_module_entry *) Z_PTR(s->val))->name);
}
/* }}} */

static void print_modules(void) /* {{{ */
{
    HashTable sorted_registry;

    zend_hash_init(&sorted_registry, 50, NULL, NULL, 0);
    zend_hash_copy(&sorted_registry, &module_registry, NULL);
    zend_hash_sort(&sorted_registry, module_name_cmp, 0);
    zend_hash_apply(&sorted_registry, print_module_info);
    zend_hash_destroy(&sorted_registry);
}
/* }}} */

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef STDERR_FILENO
#define STDERR_FILENO 2
#endif

static inline int sapi_cli_select(php_socket_t fd)
{
    fd_set wfd, dfd;
    struct timeval tv;
    int ret;

    FD_ZERO(&wfd);
    FD_ZERO(&dfd);

    PHP_SAFE_FD_SET(fd, &wfd);

    tv.tv_sec = (long) FG(default_socket_timeout);
    tv.tv_usec = 0;

    ret = php_select(fd+1, &dfd, &wfd, &dfd, &tv);

    return ret != -1;
}

PHP_CLI_API size_t sapi_cli_single_write(const char *str, size_t str_length) /* {{{ */
{
#ifdef PHP_WRITE_STDOUT
    zend_long ret;
#else
    size_t ret;
#endif

#ifdef PHP_WRITE_STDOUT
    do {
        ret = write(STDOUT_FILENO, str, str_length);
    } while (ret <= 0 && errno == EAGAIN && sapi_cli_select(STDOUT_FILENO));

    if (ret <= 0) {
        return 0;
    }

    return ret;
#else
    ret = fwrite(str, 1, MIN(str_length, 16384), stdout);
    return ret;
#endif
}
/* }}} */

static size_t sapi_cli_ub_write(const char *str, size_t str_length) /* {{{ */
{
    const char *ptr = str;
    size_t remaining = str_length;
    size_t ret;

    if (!str_length) {
        return 0;
    }

    while (remaining > 0) {
        ret = sapi_cli_single_write(ptr, remaining);
        if (!ret) {
            break;
        }
        ptr += ret;
        remaining -= ret;
    }

    return ptr - str;
}
/* }}} */

static void sapi_cli_flush(void *server_context) /* {{{ */
{
    /* Ignore EBADF here, it's caused by the fact that STDIN/STDOUT/STDERR streams
     * are/could be closed before fflush() is called.
     */
    if (fflush(stdout) == EOF && errno != EBADF) {
    }
}
/* }}} */

static void sapi_cli_register_variables(zval *track_vars_array) /* {{{ */
{
}
/* }}} */

static void sapi_cli_log_message(char *message, int syslog_type_int) /* {{{ */
{
    fprintf(stderr, "%s\n", message);
}
/* }}} */

static int sapi_cli_deactivate(void) /* {{{ */
{
    fflush(stdout);
    return SUCCESS;
}
/* }}} */

static char *sapi_cli_read_cookies(void) /* {{{ */
{
    return NULL;
}
/* }}} */

static int sapi_cli_header_handler(sapi_header_struct *h, sapi_header_op_enum op, sapi_headers_struct *s) /* {{{ */
{
    return 0;
}
/* }}} */

static int sapi_cli_send_headers(sapi_headers_struct *sapi_headers) /* {{{ */
{
    /* We do nothing here, this function is needed to prevent that the fallback
     * header handling is called. */
    return SAPI_HEADER_SENT_SUCCESSFULLY;
}
/* }}} */

static void sapi_cli_send_header(sapi_header_struct *sapi_header, void *server_context) /* {{{ */
{
}
/* }}} */

static int php_cli_startup(sapi_module_struct *sapi_module)/* {{{ */
{
    if (php_module_startup(sapi_module, NULL, 0) == FAILURE) {
        return FAILURE;
    }
    return SUCCESS;
}
/* }}} */

/* {{{ sapi_module_struct cli_sapi_module
 */
static sapi_module_struct cli_sapi_module = {
    "cli",                          /* name */
    "Command Line Interface",       /* pretty name */

    php_cli_startup,                /* startup */
    php_module_shutdown_wrapper,    /* shutdown */

    NULL,                           /* activate */
    sapi_cli_deactivate,            /* deactivate */

    sapi_cli_ub_write,              /* unbuffered write */
    sapi_cli_flush,                 /* flush */
    NULL,                           /* get uid */
    NULL,                           /* getenv */

    php_error,                      /* error handler */

    sapi_cli_header_handler,        /* header handler */
    sapi_cli_send_headers,          /* send headers handler */
    sapi_cli_send_header,           /* send header handler */

    NULL,                           /* read POST data */
    sapi_cli_read_cookies,          /* read Cookies */

    sapi_cli_register_variables,    /* register server variables */
    sapi_cli_log_message,           /* Log message */
    NULL,                           /* Get request time */
    NULL,                           /* Child terminate */

    STANDARD_SAPI_MODULE_PROPERTIES
};
/* }}} */

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
               "   %s [options] -r <code> [--] [args...]\n"
               "   %s [options] [-B <begin_code>] -R <code> [-E <end_code>] [--] [args...]\n"
               "   %s [options] [-B <begin_code>] -F <file> [-E <end_code>] [--] [args...]\n"
               "   %s [options] -S <addr>:<port> [-t docroot] [router]\n"
               "   %s [options] -- [args...]\n"
               "   %s [options] -a\n"
               "\n"
               , prog, prog, prog, prog, prog, prog, prog);
}
/* }}} */

static int do_cli(int argc, char **argv) /* {{{ */
{
    int c;
    volatile int request_started = 0;
    volatile int exit_status = 0;
    char *php_optarg = NULL;
    int php_optind = 1;

    zend_try {
        while ( (c = php_getopt(argc, argv, OPTIONS, &php_optarg, &php_optind, 0, 2)) != -1) {
            switch (c) {

            case 'i': /* php info & quit */
                if (php_request_startup() == FAILURE) {
                    goto err;
                }
                request_started = 1;
                php_print_info(0xFFFFFFFF);
                php_output_end_all();
                exit_status = (c == '?' && argc > 1 && !strchr(argv[1], c));
                goto out;

            case 'v': /* show php version & quit */
                php_printf("PHP %s (%s) (built: %s %s) ( %s)\nCopyright (c) 1997-2019 The PHP Group\n%s",
                    PHP_VERSION, cli_sapi_module.name, __DATE__, __TIME__,
#if ZTS
                    "ZTS "
#else
                    "NTS "
#endif
#ifdef COMPILER
                    COMPILER
                    " "
#endif
#ifdef ARCHITECTURE
                    ARCHITECTURE
                    " "
#endif
#if ZEND_DEBUG
                    "DEBUG "
#endif
#ifdef HAVE_GCOV
                    "GCOV "
#endif
                    ,
                    get_zend_version()
                );
                sapi_deactivate();
                goto out;

            case 'm': /* list compiled in modules */
                if (php_request_startup() == FAILURE) {
                    goto err;
                }
                request_started = 1;
                php_printf("[PHP Modules]\n");
                print_modules();
                php_printf("\n[Zend Modules]\n");
                php_printf("\n");
                php_output_end_all();
                exit_status = 0;
                goto out;

            default:
                break;
            }
        }
    } zend_end_try();

out:
    if (request_started) {
        php_request_shutdown((void *) 0);
    }
    if (exit_status == 0) {
        exit_status = EG(exit_status);
    }
    return exit_status;
err:
    sapi_deactivate();
    zend_ini_deactivate();
    exit_status = 1;
    goto out;
}
/* }}} */

/* {{{ main
 */
int main(int argc, char *argv[])
{
    int c;
    int exit_status = SUCCESS;
    int module_started = 0, sapi_started = 0;
    char *php_optarg = NULL;
    int php_optind = 1;
    sapi_module_struct *sapi_module = &cli_sapi_module;

    while ( (c = php_getopt(argc, argv, OPTIONS, &php_optarg, &php_optind, 0, 2)) != -1) {
        switch (c) {
        case 'h': /* help & quit */
        case '?':
            php_cli_usage(argv[0]);
            goto out;
        case 'i': case 'v': case 'm':
            sapi_module = &cli_sapi_module;
            goto exit_loop;
        }
    }
exit_loop:

    sapi_module->phpinfo_as_text = 1;
    sapi_startup(sapi_module);
    sapi_started = 1;

    if (sapi_module->startup(sapi_module) == FAILURE) {
        exit_status = 1;
        goto out;
    }
    module_started = 1;

    zend_first_try {
        if (sapi_module == &cli_sapi_module) {
            exit_status = do_cli(argc, argv);
        }
    } zend_end_try();
out:
    if (module_started) {
        php_module_shutdown();
    }
    if (sapi_started) {
        sapi_shutdown();
    }
    exit(exit_status);
}
/* }}} */
