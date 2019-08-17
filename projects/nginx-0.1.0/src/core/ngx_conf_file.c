
/*
 * Copyright (C) Ding Peilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


ngx_int_t ngx_conf_full_name(ngx_cycle_t *cycle, ngx_str_t *name)
{
    u_char     *p;
    ngx_str_t   old;

    if (name->data[0] == '/') {
        return NGX_OK;
    }

    old = *name;

    name->len = cycle->root.len + old.len;

    if (!(name->data = ngx_palloc(cycle->pool, name->len + 1))) {
        return NGX_ERROR;
    }

    p = ngx_cpymem(name->data, cycle->root.data, cycle->root.len);
    ngx_cpystrn(p, old.data, old.len + 1);

    return NGX_OK;
}
