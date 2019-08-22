#include <stdio.h>
#include "sds.h"
#include "zmalloc.h"

int main(void)
{
    sds s1;

    s1 = sdsnew("abc");
    printf("s1: %s, len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, "def");
    printf("s1: %s, len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, "ghijk");
    printf("s1: %s, len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, "lmnopqrst");
    printf("s1: %s, len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, "uvwxyz");
    printf("s1: %s, len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    sdsfree(s1);

    printf("\n---------------------------\n");
    printf("used memory: %zu bytes\n", zmalloc_used_memory());
    printf("---------------------------\n");
    return 0;
}
