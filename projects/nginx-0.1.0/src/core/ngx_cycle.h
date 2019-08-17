
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
    
    ngx_str_t          conf_file;
    ngx_str_t          root;
};


typedef struct {
    ngx_flag_t   daemon;
    ngx_flag_t   master;
    
    ngx_int_t    woker_processes;

    // ngx_uid_t    user;
    // ngx_gid_t    group;

    ngx_str_t    pid;
    ngx_str_t    newpid;
} ngx_core_conf_t;


ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle);


extern volatile ngx_cycle_t  *ngx_cycle;
extern ngx_uint_t             ngx_test_config;


#endif /* _NGX_CYCLE_H_INCLUDED_ */
