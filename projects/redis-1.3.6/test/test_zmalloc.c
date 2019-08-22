#include <stdio.h>
#include <string.h>
#include "zmalloc.h"

struct User {
    int id;
    short age;
    char name[25];
};

int main(void)
{
    int *a;
    char *s;
    struct User *user;

    printf("sizeof(short)  = %zu\n", sizeof(short));
    printf("sizeof(int)    = %zu\n", sizeof(int));
    printf("sizeof(long)   = %zu\n", sizeof(long));
    printf("sizeof(size_t) = %zu\n", sizeof(size_t));
    printf("------------------------------------\n\n");

    // 分配内存
    a = zmalloc(sizeof(int));
    printf("after zmalloc int : %zu bytes\n", zmalloc_used_memory()); 

    s = zmalloc(sizeof(10));
    printf("after zmalloc str : %zu bytes\n", zmalloc_used_memory()); 

    user = zmalloc(sizeof(struct User));
    printf("after zmalloc User: %zu bytes\n", zmalloc_used_memory()); 

    printf("------------------------------------\n\n");

    // 释放内存
    zfree(a);
    printf("after zfree int : %zu bytes\n", zmalloc_used_memory());

    zfree(s);
    printf("after zfree str : %zu bytes\n", zmalloc_used_memory());

    zfree(user);
    printf("after zfree User: %zu bytes\n", zmalloc_used_memory());

    printf("------------------------------------\n\n");

    // zrealloc
    s = zmalloc(6);
    strcpy(s, "hello");
    printf("s: %s, used_memory: %zu bytes\n", s, zmalloc_used_memory());

    s = zrealloc(s, 15);
    strcat(s, " world!");
    printf("s: %s, used_memory: %zu bytes\n", s, zmalloc_used_memory());

    zfree(s);
    printf("used_memory: %zu bytes\n", zmalloc_used_memory());

    printf("------------------------------------\n\n");

    // 打印内存使用情况
    printf("used memory: %zu bytes\n", zmalloc_used_memory());
    return 0;
}
