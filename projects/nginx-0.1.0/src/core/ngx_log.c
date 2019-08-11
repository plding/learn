
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


static void ngx_log_write(ngx_log_t *log, char *errstr, size_t len);


static ngx_log_t        ngx_log;
static ngx_open_file_t  ngx_stderr;


static const char *err_levels[] = {
    "stderr", "emerg", "alert", "crit", "error",
    "warn", "notice", "info", "debug"
};

static const char *debug_levels[] = {
    "debug_core", "debug_alloc", "debug_mutex", "debug_event",
    "debug_http", "debug_imap"
};


#if (HAVE_VARIADIC_MACROS)
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
                        const char *fmt, ...)
#else
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
                        const char *fmt, va_list args)
#endif
{
    char      errstr[MAX_ERROR_STR];
    size_t    len, max;
#if (HAVE_VARIADIC_MACROS)
    va_list   args;
#endif

    // if (log->file->fd == NGX_INVALID_FILE) {
    //     return;
    // }

#if (WIN32)
    max = MAX_ERROR_STR - 2;
#else
    max = MAX_ERROR_STR - 1;
#endif

    len = 0;
    len += ngx_snprintf(errstr + len, max - len, " [%s] ", err_levels[level]);

    /* pid#tid */

    if (log->data && *(int *) log->data != -1) {
        len += ngx_snprintf(errstr + len, max - len,
                            "*%u", *(u_int *) log->data);
    }

#if (HAVE_VARIADIC_MACROS)

    va_start(args, fmt);
    len += ngx_vsnprintf(errstr + len, max - len, fmt, args);
    va_end(args);

#else

    len += ngx_vsnprintf(errstr + len, max - len, fmt, args);

#endif

    ngx_log_write(log, errstr, len);
}


static void ngx_log_write(ngx_log_t *log, char *errstr, size_t len)
{
    errstr[len++] = LF;
    write(log->file->fd, errstr, len);
} 


#if !(HAVE_VARIADIC_MACROS)

void ngx_log_debug_core(ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
    va_list    args;

    va_start(args, fmt);
    ngx_log_error_core(NGX_LOG_DEBUG, log, err, fmt, args);
    va_end(args);
}

#endif


ngx_log_t *ngx_log_init_stderr()
{
    ngx_stderr.fd = STDERR_FILENO;

    ngx_log.file = &ngx_stderr;
    ngx_log.log_level = 0xff8;

    return &ngx_log;    
}
