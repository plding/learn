
/*
 * Copyright (C) Ding Peilong
 */


#ifndef _NGX_CONFIG_H_INCLUDED_
#define _NGX_CONFIG_H_INCLUDED_


#if defined __DragonFly__ && !defined __FreeBSD__
#define __FreeBSD__        4
#define __FreeBSD_version  480101
#endif


#if defined __FreeBSD__
#include <ngx_freebsd_config.h>


#elif defined __linux__
#include <ngx_linux_config.h>


/* Solaris */
#elif defined sun && (defined __svr4__ || defined __SVR4)
#include <ngx_solaris_config.h>


#elif defined _WIN32
#include <ngx_win32_config.h>


#else /* posix */
#include <ngx_posix_config.h>

#endif


typedef int                ngx_int_t;
typedef u_int              ngx_uint_t;
typedef int                ngx_flag_t;
#define NGX_INT_T_LEN      sizeof("-2147483648") - 1
#define NGX_INT_T_FMT      "d"
#define NGX_UINT_T_FMT     "u"


#define NGX_INT32_LEN      sizeof("-2147483648") - 1
#define NGX_INT64_LEN      sizeof("-9223372036854775808") - 1
#define NGX_OFF_T_LEN      sizeof("-9223372036854775808") - 1


#define NGX_ALIGN       (sizeof(unsigned long) - 1)  /* platform word */
#define NGX_ALIGN_CAST  (unsigned long)              /* size of the pointer */

#define ngx_align(p)    (char *) ((NGX_ALIGN_CAST p + NGX_ALIGN) & ~NGX_ALIGN)


#ifndef ngx_inline
#define ngx_inline   inline
#endif


#endif /* _NGX_CONFIG_H_INCLUDED_ */
