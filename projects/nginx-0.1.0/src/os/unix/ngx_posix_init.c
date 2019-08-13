
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


int ngx_os_init(ngx_log_t *log)
{
    return ngx_posix_init(log);
}


ngx_int_t ngx_posix_init(ngx_log_t *log)
{
    ngx_pagesize = getpagesize();

    return NGX_OK;
}
