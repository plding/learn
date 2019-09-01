#ifndef ADLIST_H
#define ADLIST_H

// 结构体
// 链表结点
typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

// 双端链表
typedef struct list {
    listNode *head;
    listNode *tail;
    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);
    size_t len;
} list;

// 迭代器
typedef struct listIter {
    listNode *next;
    int direction;
} listIter;

// 函数原型和宏定义
#define listLength(l)               ((l)->len)
#define listFirst(l)                ((l)->head)
#define listLast(l)                 ((l)->tail)
#define listPrevNode(n)             ((n)->prev)
#define listNextNode(n)             ((n)->next)
#define listNodeValue(n)            ((n)->value)

#define listSetDupMethod(l, m)      ((l)->dup = (m))
#define listSetFreeMethod(l, m)     ((l)->free = (m))
#define listSetMatchMethod(l, m)    ((l)->match = (m))

#define listGetDupMethod(l, m)      ((l)->dup)
#define listGetFreeMethod(l, m)     ((l)->free)
#define listGetMatchMethod(l, m)    ((l)->match)

list *listCreate(void);
void  listRelease(list *list);
list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
void  listDelNode(list *list, listNode *node);
listNode *listSearchKey(const list *list, void *key);
listNode *listIndex(const list *list, int index);
list *listDup(const list *list);

listIter *listGetIterator(const list *list, int direction);
listNode *listNext(listIter *iter);
void      listRewind(const list *list, listIter *iter);
void      listRewindTail(const list *list, listIter *iter);
void      listReleaseIterator(listIter *iter);

// 迭代器遍历方向
#define AL_START_HEAD 0 
#define AL_START_TAIL 1 

#endif /* ADLIST_H */
