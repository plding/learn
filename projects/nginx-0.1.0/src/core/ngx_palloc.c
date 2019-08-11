
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log)
{
    ngx_pool_t  *p;

    if (!(p = ngx_alloc(size, log))) {
        return NULL;
    }

    p->last  = (char *) p + sizeof(ngx_pool_t);
    p->end   = (char *) p + size;
    p->next  = NULL;
    p->large = NULL;
    p->log   = log;

    return p;
}
