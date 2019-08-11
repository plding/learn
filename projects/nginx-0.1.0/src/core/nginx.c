
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <nginx.h>


int main(int argc, char *const *argv)
{
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

    // cycle = ngx_init_cycle(&init_cycle);
    // if (cycle == NULL) {
    //     return 1;
    // }

    return 0;
}
