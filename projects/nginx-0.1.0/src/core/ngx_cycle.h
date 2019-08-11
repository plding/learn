
/*
 * Copyright (C) Ding Peilong
 */


#ifndef _NGX_CYCLE_H_INCLUDED_
#define _NGX_CYCLE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


struct ngx_cycle_s {
    void           ****conf_ctx;
    ngx_pool_t        *pool;
    
    ngx_log_t         *log;
    ngx_log_t         *new_log;

    ngx_cycle_t       *old_cycle;
};


#endif /* _NGX_CYCLE_H_INCLUDED_ */
