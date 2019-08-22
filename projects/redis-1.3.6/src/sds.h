#ifndef SDS_H
#define SDS_H

typedef char *sds;

struct sdshdr {
    size_t len;
    size_t free;
    char buf[];
};

sds sdsnewlen(const char *init, size_t initlen);
sds sdsnew(const char *init);
sds sdsempty();
sds sdsdup(const sds s);
sds sdscat(sds s, char *t);
sds sdscatlen(sds s, char *t, size_t len);
void sdsfree(sds s);

size_t sdslen(const sds s);
size_t sdsavail(const sds s);

#endif /* SDS_H */
