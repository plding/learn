#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "sds.h"
#include "zmalloc.h"

/*
 * 用指定字符串和指定长度初始化sds
 *
 * ```
 * sds s;
 *
 * // s->len   = 10;
 * // s->free  = 0;
 * // s->buf[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', '\0'};
 * s = sdsnewlen("hello world", 10);
 * ``` 
 */
sds sdsnewlen(const char *init, size_t initlen)
{
    struct sdshdr *sh;

    // 注意: 申请的空间长度 = sdshdr结构体的长度 + 指定的初始化长度 + 1 (用来存放字符串结尾的\0)
    sh = zmalloc(sizeof(struct sdshdr) + initlen + 1); 

    // 新创建的sds, len等于指定的初始化长度, free等于0
    sh->len  = initlen;
    sh->free = 0;

    // 如果初始化长度不为零, 初始化内容
    if (initlen) {
        if (init) {
            memcpy(sh->buf, init, initlen);
        } else {
            memset(sh->buf, '\0', initlen);
        }
    }
    sh->buf[initlen] = '\0';    // 追加'\0'

    // 返回buf字段的地址
    return sh->buf;
}

/*
 * 用指定字符串初始化sds
 */
sds sdsnew(const char *init)
{
    return sdsnewlen(init, init ? strlen(init) : 0);
}

/*
 * 初始化一个空的sds
 */
sds sdsempty()
{
    return sdsnewlen(NULL, 0);
}

/*
 * 拷贝一个新的sds
 */
sds sdsdup(const sds s)
{
    return sdsnewlen(s, sdslen(s));
}

/*
 * 释放sds
 */
void sdsfree(sds s)
{
    // 注意要从申请的首字节开始释放内存
    struct sdshdr *sh = (struct sdshdr *) (s - sizeof(struct sdshdr));
    zfree(sh);
}

/*
 * 获取sds已使用的长度
 */
size_t sdslen(const sds s)
{
    struct sdshdr *sh = (struct sdshdr *) (s - sizeof(struct sdshdr));
    return sh->len;
}

/*
 * 获取sds剩余可用的长度
 */
size_t sdsavail(const sds s)
{
    struct sdshdr *sh = (struct sdshdr *) (s - sizeof(struct sdshdr));
    return sh->free;
}

/*
 * 判断是否需要扩大空间
 *
 * 1. 如果剩余长度 > 要追加的长度, 返回原来的sdshdr
 * 2. 否则, 将新的可用长度扩大两倍, 申请新的空间
 */
static struct sdshdr *sdsMakeRoomFor(sds s, size_t addlen)
{
    struct sdshdr *sh, *newsh;
    size_t oldlen, newlen;

    sh = (struct sdshdr *) (s - sizeof(struct sdshdr)); 

    // 剩余空间足够放下要追加的内容, 直接返回原来的sdshdr
    if (sh->free > addlen) {
        return sh;
    }

    oldlen = sh->len;
    
    // 新的长度 = (原来长度 + 追加长度) * 2
    newlen = (oldlen + addlen) * 2;

    // 重新申请内存
    newsh = zrealloc(sh, sizeof(struct sdshdr) + newlen + 1);

    // 新的len == 老的len, realloc时已经复制过来了, 不用更改了
    // 新的剩余长度 = 新的长度 - 老的长度
    newsh->free = newlen - oldlen;

    // 返回新的sdshdr
    return newsh;
}

/*
 * 拷贝指定长度的字符串到sds中
 */
sds sdscpylen(sds s, char *t, size_t len)
{
    struct sdshdr *sh = (struct sdshdr *) (s - sizeof(struct sdshdr));    
    size_t totlen = sh->len + sh->free;

    if (totlen < len) {
        sh = sdsMakeRoomFor(s, len - sh->len);
        totlen = sh->len + sh->free;
    }

    memcpy(sh->buf, t, len);
    sh->buf[len] = '\0';
    sh->len  = len;
    sh->free = totlen - len;

    return sh->buf;
}

/*
 * 拷贝指定字符串到sds中
 */
sds sdscpy(sds s, char *t)
{
    return sdscpylen(s, t, strlen(t));
}

/*
 * 向sds中追加指定长度的字符串
 */
sds sdscatlen(sds s, char *t, size_t len)
{
    struct sdshdr *sh;

    // 判断是否需要扩大空间
    sh = sdsMakeRoomFor(s, len);
    
    // 拷贝内存
    memcpy(sh->buf + sh->len, t, len);
    // 追加'\0'
    sh->buf[sh->len+len] = '\0';

    // 重新调整len和free的大小 
    sh->len  += len;
    sh->free -= len;

    return sh->buf;
}

/*
 * 向sds中追加字符串
 */
sds sdscat(sds s, char *t)
{
    return sdscatlen(s, t, strlen(t));
}

/*
 * 去除sds首尾指定字符
 */
sds sdstrim(sds s, const char *cset)
{
    struct sdshdr *sh = (struct sdshdr *) (s - sizeof(struct sdshdr));
    char *sp, *ep, *end;
    size_t len;

    // 尾指针
    end = s + sdslen(s);

    // 遍历
    for (sp = s; sp < end && strchr(cset, *sp); sp++)
        ;
    for (ep = end - 1; ep > sp && strchr(cset, *ep); ep--)
        ;
    
    // 结果字符串长度
    len = ep - sp + 1;

    // 如果起始位置发生了改变, 需要拷贝内存
    if (sp != s) {
        memmove(s, sp, len);
    }
    s[len] = '\0'; // 结尾'\0'

    // 重新设置free和len
    sh->free += sh->len - len;
    sh->len   = len;

    // 返回新的sds
    return s;
}

/*
 * sds转小写
 */
void sdstolower(sds s)
{
    for (char *p = s, *end = s + sdslen(s); p < end; ++p) {
        *p = tolower(*p);
    }
}

/*
 * sds转大写
 */
void sdstoupper(sds s)
{
    for (char *p = s, *end = s + sdslen(s); p < end; ++p) {
        *p = toupper(*p);
    }
}

/*
 * sds比较
 */
int sdscmp(const sds s1, const sds s2)
{
    size_t len1, len2, len;
    int cmp;

    len1 = sdslen(s1);
    len2 = sdslen(s2);
    
    if (len1 == len2) {
        return memcmp(s1, s2, len1);
    }

    len = len1 < len2 ? len1 : len2;
    cmp = memcmp(s1, s2, len);

    if (cmp == 0) {
        cmp = len1 - len2;
    }

    return cmp;
}
