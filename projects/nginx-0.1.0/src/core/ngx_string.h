
/*
 * Copyright (C) Ding Peilong
 */


#ifndef _NGX_STRING_H_INCLUDED_
#define _NGX_STRING_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    size_t     len;
    u_char    *data;
} ngx_str_t;


#define ngx_string(str)  { sizeof(str) - 1, (u_char *) str }
#define ngx_null_string  { 0, NULL }


#define ngx_strncasecmp(s1, s2, n)                                           \
                          strncasecmp((const char *) s1, (const char *) s2, n)
#define ngx_strcasecmp(s1, s2)                                               \
                          strcasecmp((const char *) s1, (const char *) s2)

#define ngx_snprintf      snprintf
#define ngx_vsnprintf     vsnprintf


#define ngx_strncmp(s1, s2, n)                                               \
                            strncmp((const char *) s1, (const char *) s2, n)

/* msvc and icc compile strcmp() to inline loop */
#define ngx_strcmp(s1, s2)  strcmp((const char *) s1, (const char *) s2)

#define ngx_strstr(s1, s2)  strstr((const char *) s1, (const char *) s2)
#define ngx_strlen(s)       strlen((const char *) s)

/*
 * msvc and icc compile memset() to the inline "rep stos"
 * while ZeroMemory() and bzero() are the calls.
 * icc may also inline several mov's of a zeroed register for small blocks.
 */
#define ngx_memzero(buf, n)       memset(buf, 0, n)

/* msvc and icc compile memcpy() to the inline "rep movs" */
#define ngx_memcpy(dst, src, n)   memcpy(dst, src, n)
#define ngx_cpymem(dst, src, n)   ((u_char *) memcpy(dst, src, n)) + n

/* msvc and icc compile memcmp() to the inline loop */
#define ngx_memcmp                memcmp


#endif /* _NGX_STRING_H_INCLUDED_ */
