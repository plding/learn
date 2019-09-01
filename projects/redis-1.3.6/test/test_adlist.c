#include <stdio.h>
#include "adlist.h"
#include "zmalloc.h"

void dumpList(list *list);

int main(void)
{
    list *l1;
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

    // 打印链表信息
    dumpList(l1);

    // 查找指定结点
    node = listSearchKey(l1, (void *)(intptr_t) 7);
    if (node != NULL) {
        printf("found 7!\n");
        // 删除该结点
        listDelNode(l1, node);
    } else {
        printf("not found 7!\n");
    }

    node = listSearchKey(l1, (void *)(intptr_t) 11);
    if (node != NULL) {
        printf("found 11!\n");
        // 删除该结点
        listDelNode(l1, node);
    } else {
        printf("not found 11!\n");
    }

    // 再次打印链表信息
    dumpList(l1);

    // 释放链表
    listRelease(l1);

    // 打印内存使用情况
    printf("\n---------------------------\n");
    printf("used memory: %zu bytes\n", zmalloc_used_memory());
    printf("---------------------------\n");
    return 0;
}

void dumpList(list *list)
{
    listIter *iter;
    listNode *node;

    // 打印链表长度
    printf("len: %zu\n", list->len);

    // 打印链表元素
    printf("values:");
    iter = listGetIterator(list, AL_START_HEAD);
    while ((node = listNext(iter)) != NULL) {
        printf(" %d", (int) listNodeValue(node));
    }
    listReleaseIterator(iter);
    printf("\n");

}
