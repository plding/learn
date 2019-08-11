
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle)
{
    ngx_log_t          *log;
    ngx_pool_t         *pool;
    ngx_cycle_t        *cycle;

    log = old_cycle->log;

    if (!(pool = ngx_create_pool(16 * 1024, log))) {
        return NULL;
    }
    pool->log = log;

    if (!(cycle = ngx_pcalloc(pool, sizeof(ngx_cycle_t)))) {
        ngx_destroy_pool(pool);
        return NULL;
    }
    cycle->pool = pool;
    cycle->old_cycle = old_cycle;

    return cycle;
}
