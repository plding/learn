#include <stdio.h>
#include "adlist.h"
#include "zmalloc.h"

void dumpList(const char *msg, list *list);

int main(void)
{
    list *l1;
    listIter *iter;
    listNode *node;

    // 创建链表
    l1 = listCreate();

    // 从后端插入元素
    for (int i = 0; i < 5; ++i) {
        listAddNodeTail(l1, (void *)(intptr_t) i);
    }
    // 从前端插入元素
    for (int i = 0; i < 5; ++i) {
        listAddNodeHead(l1, (void *)(intptr_t) (i + 5));
    }

    // 打印链表长度
    printf("l1->len: %zu\n", l1->len);

    // 打印链表元素
    printf("l1->values:");
    iter = listGetIterator(l1, AL_START_HEAD);
    while ((node = listNext(iter)) != NULL) {
        printf(" %d", (int) listNodeValue(node));
    }
    listReleaseIterator(iter);
    printf("\n");

    // 释放链表
    listRelease(l1);

    // 打印内存使用情况
    printf("\n---------------------------\n");
    printf("used memory: %zu bytes\n", zmalloc_used_memory());
    printf("---------------------------\n");
    return 0;
}
