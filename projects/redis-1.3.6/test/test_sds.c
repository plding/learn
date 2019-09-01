#include <stdio.h>
#include "sds.h"
#include "zmalloc.h"

int main(void)
{
    sds s1, s2;

    // strcpy & strcat
    s1 = sdsempty();
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscpy(s1, "hello");
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, " ");
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, "world");
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    s1 = sdscat(s1, "!");
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));

    sdsfree(s1);

    // strtrim
    s1 = sdsnew(" \thello  world !!\t\n   ");
    s1 = sdstrim(s1, " \t\n");
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));
    sdsfree(s1);

    s1 = sdsnew(" \t \n ");
    s1 = sdstrim(s1, " \t\n");
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));
    sdsfree(s1);

    // sdstolower & sdstoupper
    s1 = sdsnew("This is a test.");
    sdstolower(s1);
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));
    sdstoupper(s1);
    printf("s1: '%s', len: %zu, free: %zu\n", s1, sdslen(s1), sdsavail(s1));
    sdsfree(s1);

    // sdscmp
    s1 = sdsnew("abc");
    s2 = sdsnew("abd");
    printf("sdscmp(s1, s2): %d\n", sdscmp(s1, s2));
    printf("sdscmp(s2, s1): %d\n", sdscmp(s2, s1));
    sdsfree(s1);
    sdsfree(s2);

    s1 = sdsnew("abcde");
    s2 = sdsnew("abc");
    printf("sdscmp(s1, s2): %d\n", sdscmp(s1, s2));
    printf("sdscmp(s2, s1): %d\n", sdscmp(s2, s1));
    sdsfree(s1);
    sdsfree(s2);

    s1 = sdsnew("abc");
    s2 = sdsnew("abc");
    printf("sdscmp(s1, s2): %d\n", sdscmp(s1, s2));
    sdsfree(s1);
    sdsfree(s2);

    printf("\n---------------------------\n");
    printf("used memory: %zu bytes\n", zmalloc_used_memory());
    printf("---------------------------\n");
    return 0;
}
