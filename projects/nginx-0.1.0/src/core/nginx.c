
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <nginx.h>


static void *ngx_core_module_create_conf(ngx_cycle_t *cycle);
static char *ngx_core_module_init_conf(ngx_cycle_t *t, void *conf);


static ngx_command_t  ngx_core_commands[] = {

    // { ngx_string("daemon"),
    //   NGX_MAIN_CONF|NGX_DIRECT_CONF|NGX_CONF_TAKE1,
    //   ngx_conf_set_flag_slot,
    //   0,
    //   offsetof(ngx_core_conf_t, daemon),
    //   NULL },

    ngx_null_command
};


static ngx_core_module_t  ngx_core_module_ctx = {
    ngx_string("core"),
    ngx_core_module_create_conf,
    ngx_core_module_init_conf
};


ngx_module_t  ngx_core_module = {
    NGX_MODULE,
    &ngx_core_module_ctx,                  /* module context */
    ngx_core_commands,                     /* module directives */
    NGX_CORE_MODULE,                       /* module type */
    NULL,                                  /* init module */
    NULL                                   /* init process */
};


ngx_uint_t ngx_max_module;


int main(int argc, char *const *argv)
{
    ngx_int_t          i;
    ngx_log_t         *log;
    ngx_cycle_t       *cycle, init_cycle;
    ngx_master_ctx_t   ctx;

    if (!(log = ngx_log_init_stderr())) {
        return 1;
    }

    /* init_cycle->log is required for signal handlers and ngx_getopt() */

    ngx_memzero(&init_cycle, sizeof(ngx_cycle_t));
    init_cycle.log = log;

    ngx_memzero(&ctx, sizeof(ngx_master_ctx_t));
    ctx.argc = argc;
    ctx.argv = argv;

    if (!(init_cycle.pool = ngx_create_pool(1024, log))) {
        return 1;
    }

    if (ngx_os_init(log) == NGX_ERROR) {
        return 1;
    }

    ngx_max_module = 0;
    for (i = 0; ngx_modules[i]; ++i) {
        ngx_modules[i]->index = ngx_max_module++;
    }

    // cycle = ngx_init_cycle(&init_cycle);
    // if (cycle == NULL) {
    //     return 1;
    // }

    return 0;
}


static void *ngx_core_module_create_conf(ngx_cycle_t *cycle)
{
    ngx_core_conf_t  *ccf;

    if (!(ccf = ngx_pcalloc(cycle->pool, sizeof(ngx_core_conf_t)))) {
        return NULL;
    }

    return ccf;
}


static char *ngx_core_module_init_conf(ngx_cycle_t *cycle, void *conf)
{
    return NGX_CONF_OK;
}
