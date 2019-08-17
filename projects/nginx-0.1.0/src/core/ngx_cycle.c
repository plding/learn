
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


volatile ngx_cycle_t  *ngx_cycle;

ngx_uint_t             ngx_test_config;


ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle)
{
    void               *rv;
    ngx_uint_t          i;
    ngx_log_t          *log;
    ngx_pool_t         *pool;
    ngx_cycle_t        *cycle;
    ngx_core_module_t  *module;

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


    cycle->conf_ctx = ngx_pcalloc(pool, ngx_max_module * sizeof(void *));
    if (cycle->conf_ctx == NULL) {
        ngx_destroy_pool(pool);
        return NULL;
    }


    for (i = 0; ngx_modules[i]; ++i) {
        if (ngx_modules[i]->type != NGX_CORE_MODULE) {
            continue;
        } 

        module = ngx_modules[i]->ctx;

        if (module->create_conf) {
            rv = module->create_conf(cycle);
            if (rv == NGX_CONF_ERROR) {
                ngx_destroy_pool(pool);
                return NULL;
            }
            cycle->conf_ctx[ngx_modules[i]->index] = rv;
        }
    }


    for (i = 0; ngx_modules[i]; ++i) {
        if (ngx_modules[i]->type != NGX_CORE_MODULE) {
            continue;
        }

        module = ngx_modules[i]->ctx;

        if (module->init_conf) {
            if (module->init_conf(cycle, cycle->conf_ctx[ngx_modules[i]->index])
                                                              == NGX_CONF_ERROR)
            {
                ngx_destroy_pool(pool);
                return NULL;
            }
        }
    }

    return cycle;
}
