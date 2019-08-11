
/*
 * Copyright (C) Ding Peilong
 */


#ifndef _NGX_PROCESS_CYCLE_H_INCLUDED_
#define _NGX_PROCESS_CYCLE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    int           argc;
    char *const  *argv;
} ngx_master_ctx_t;


#define NGX_PROCESS_SINGLE   0
#define NGX_PROCESS_MASTER   1
#define NGX_PROCESS_WORKER   2


#endif /* _NGX_PROCESS_CYCLE_H_INCLUDED_ */
