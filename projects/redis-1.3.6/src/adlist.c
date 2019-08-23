#include <stdlib.h>
#include "adlist.h"
#include "zmalloc.h"

/*
 * 新建链表
 */
list *listCreate(void)
{
    struct list *list;

    // 申请内存
    list = zmalloc(sizeof(struct list));

    // 初始化各个字段
    list->head  = list->tail = NULL;
    list->dup   = NULL;
    list->free  = NULL;
    list->match = NULL;
    list->len   = 0;

    // 返回链表
    return list;
}

/*
 * 释放链表
 */
void listRelease(list *list)
{
    unsigned int len;
    listNode *current, *next;

    current = list->head;
    len = list->len;

    // 遍历链表结构, 依次释放每个链表结点
    while (len--) {

        // 要先把next结点存起来, 因为待会要释放current结点, 就无法获取next结点了
        next = current->next;

        // 如果设置了free函数指针, 调用free函数释放元素的值
        if (list->free) {
            list->free(current->value);
        }

        // 释放当前结点
        zfree(current);

        // 指向下一个结点
        current = next;
    }

    // 释放链表本身
    zfree(list);
}

/*
 * 从链表的头部插入新元素
 */
list *listAddNodeHead(list *list, void *value)
{
    // 申请内存
    listNode *node = zmalloc(sizeof(listNode));
    // 设置结点值
    node->value = value;

    if (list->len) {
        // 如果链表不为空, 让新结点的next指针指向当前链表的头结点, 原先头结点的prev指针指向新结点,
        // 最后设置链表的头结点为新结点
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    } else {
        // 如果链表为空, 让链表的head和tail指针都指向新结点, 新结点的prev和next指针都指向NULL
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }
    list->len++;    // 链表长度加1

    return list;
}

/*
 * 从链表的尾部插入新元素
 */
list *listAddNodeTail(list *list, void *value)
{
    // 申请内存
    listNode *node = zmalloc(sizeof(listNode));
    // 设置结点值
    node->value = value;

    if (list->len) {
        // 如果链表不为空, 让新结点的prev指针指向当前链表的尾结点, 原先尾结点的next指针指向新结点,
        // 最后设置链表的尾结点为新结点
        node->prev = list->tail;
        node->next = NULL; 
        list->tail->next = node;
        list->tail = node;
    } else {
        // 如果链表为空, 让链表的head和tail指针都指向新结点, 新结点的prev和next指针都指向NULL
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }
    list->len++;    // 链表长度加1

    return list;
}

/*
 * 获取链表迭代器
 */
listIter *listGetIterator(list *list, int direction)
{
    // 申请内存
    listIter *iter = zmalloc(sizeof(listIter));

    // 迭代器方向
    iter->direction = direction;

    // 如果迭代器是从头开始遍历的, next指针指向头结点; 否则next指针指向尾结点
    if (iter->direction == AL_START_HEAD) {
        iter->next = list->head;
    } else {
        iter->next = list->tail;
    }

    // 返回迭代器
    return iter;
}

/*
 * 迭代器遍历
 */
listNode *listNext(listIter *iter)
{
    // 当前结点
    listNode *current = iter->next;

    // 当前结点不为空, 继续遍历下一个结点
    if (current != NULL) {
        if (iter->direction == AL_START_HEAD) {
            iter->next = current->next;
        } else {
            iter->next = current->prev;
        }
    }

    // 返回当前结点
    return current;
}

/*
 * 当迭代器重置到链表头部
 */
void listRewind(list *list, listIter *iter)
{
    iter->next = list->head;
    iter->direction = AL_START_HEAD;
}

/*
 * 当迭代器重置到链表尾部
 */
void listRewindTail(list *list, listIter *iter)
{
    iter->next = list->tail;
    iter->direction = AL_START_TAIL;
}

/*
 * 释放迭代器
 */
void listReleaseIterator(listIter *iter)
{
    zfree(iter);
}
