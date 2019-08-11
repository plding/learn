
/*
 * Copyright (C) Ding Peilong
 */


#ifndef _NGX_PALLOC_H_INCLUDED_
#define _NGX_PALLOC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct ngx_pool_large_s  ngx_pool_large_t;

struct ngx_pool_large_s {
    ngx_pool_large_t  *next;
    void              *alloc;
};


struct ngx_pool_s {
    char              *last;
    char              *end;
    ngx_pool_t        *next;
    ngx_pool_large_t  *large;
    ngx_log_t         *log;
};


void *ngx_alloc(size_t size, ngx_log_t *log);
void *ngx_calloc(size_t size, ngx_log_t *log);

ngx_pool_t *ngx_create_pool(size_t size, ngx_log_t *log);


#endif /* _NGX_PALLOC_H_INCLUDED_ */
