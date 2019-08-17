
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <nginx.h>


static ngx_int_t ngx_getopt(ngx_master_ctx_t *ctx, ngx_cycle_t *cycle);
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
    ngx_cycle = &init_cycle;

    ngx_memzero(&ctx, sizeof(ngx_master_ctx_t));
    ctx.argc = argc;
    ctx.argv = argv;

    if (!(init_cycle.pool = ngx_create_pool(1024, log))) {
        return 1;
    }

    if (ngx_getopt(&ctx, &init_cycle) == NGX_ERROR) {
        return 1;
    }

    if (ngx_test_config) {
        log->log_level = NGX_LOG_INFO;
    }

    if (ngx_os_init(log) == NGX_ERROR) {
        return 1;
    }

    ngx_max_module = 0;
    for (i = 0; ngx_modules[i]; ++i) {
        ngx_modules[i]->index = ngx_max_module++;
    }

    cycle = ngx_init_cycle(&init_cycle);
    if (cycle == NULL) {
        return 1;
    }

    return 0;
}


static ngx_int_t ngx_getopt(ngx_master_ctx_t *ctx, ngx_cycle_t *cycle)
{
    ngx_int_t  i;

    for (i = 1; i < ctx->argc; ++i) {
        if (ctx->argv[i][0] != '-') {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                          "invalid option: \"%s\"", ctx->argv[i]);
            return NGX_ERROR;
        }

        switch (ctx->argv[i][1]) {
        
        case 't':
            ngx_test_config = 1;
            break;

        case 'c':
            if (ctx->argv[i + 1] == NULL) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                              "the option: \"%s\" requires file name",
                              ctx->argv[i]);
                return NGX_ERROR;
            }

            cycle->conf_file.data = (u_char *) ctx->argv[++i];
            cycle->conf_file.len  = ngx_strlen(cycle->conf_file.data);
            break;

        default:
            ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                          "invalid option: \"%s\"", ctx->argv[i]);
            return NGX_ERROR;
        }
    }

    if (cycle->conf_file.data == NULL) {
        cycle->conf_file.data = (u_char *) NGX_CONF_PATH;
        cycle->conf_file.len  = sizeof(NGX_CONF_PATH) - 1;
    }

    if (ngx_conf_full_name(cycle, &cycle->conf_file) == NGX_ERROR) {
        return NGX_ERROR;
    }

    ngx_log_error(NGX_LOG_INFO, cycle->log, 0, "conf_file: %s", cycle->conf_file.data); 
    return NGX_OK;
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
