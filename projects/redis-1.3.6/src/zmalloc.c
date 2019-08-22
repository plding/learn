#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zmalloc.h"

// 保存分配内存的长度
#define PREFIX_SIZE sizeof(size_t)

// 已使用内存计数
static size_t used_memory = 0;

/*
 * 内存分配溢出
 * 打印错误信息, 触发SIGABRT信号, 结束当前进程
 */
static void zmalloc_oom(size_t size)
{
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
            size);
    fflush(stderr);
    abort();    // 触发SIGABRT信号
}

/*
 * 分配内存
 */
void *zmalloc(size_t size)
{
    void *ptr;
    
    // 分配size + PREFIX_SIZE长度的内存, 其中前面PREFIX_SIZE长度的
    // 内存存放实际要分配的内存长度(size)
    ptr = malloc(size + PREFIX_SIZE);

    // 内存分配失败, 报错
    if (!ptr) {
        zmalloc_oom(size);
    }

    // 将实际要分配的内存长度size 写入前PREFIX_SIZE字节
    *((size_t *) ptr) = size;

    // 增加内存使用计数
    used_memory += size + PREFIX_SIZE;

    // 返回分配的内存中第PREFIX_SIZE处的地址
    return (char *) ptr + PREFIX_SIZE;
}

/*
 * 重新分配内存
 */
void *zrealloc(void *ptr, size_t size)
{
    void *realptr;    
    size_t oldsize;
    void *newptr;

    // 如果原始地址为NULL, 直接分配新内存就好了
    if (!ptr) {
        return zmalloc(size);
    }

    // 找到实际分配内存的起始地址
    realptr = (char *) ptr - PREFIX_SIZE;
    // 获取这段内存的长度
    oldsize = *((size_t *) realptr);

    // 重新分配新内存
    // 如果分配成功, realptr会被自动释放, 所以这里不用再释放realptr
    newptr = realloc(realptr, size + PREFIX_SIZE);
    if (!newptr) {
        zmalloc_oom(size); 
    }

    // 写入新的内存长度
    *((size_t *) newptr) = size;
    // 更新内存使用计数
    used_memory += size - oldsize;

    // 返回第PREFIX_SIZE字节处的内存地址
    return (char *) newptr + PREFIX_SIZE;
}

/*
 * 释放内存
 */
void zfree(void *ptr)
{
    void *realptr;

    // 找到实际分配内存的起始地址
    realptr = ptr - PREFIX_SIZE;

    // 减少内存使用计数
    used_memory -= *((size_t *) realptr) + PREFIX_SIZE;

    // 释放内存
    free(realptr);
}

/*
 * 获取使用的内存计数
 */
size_t zmalloc_used_memory()
{
    return used_memory;
}
