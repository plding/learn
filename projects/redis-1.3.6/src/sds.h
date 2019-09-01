#ifndef SDS_H
#define SDS_H

typedef char *sds;

struct sdshdr {
    size_t len;
    size_t free;
    char buf[];
};

sds    sdsnewlen(const char *init, size_t initlen);
sds    sdsnew(const char *init);
sds    sdsempty();
sds    sdsdup(const sds s);
size_t sdslen(const sds s);
size_t sdsavail(const sds s);
void   sdsfree(sds s);
sds    sdscpy(sds s, char *t);
sds    sdscpylen(sds s, char *t, size_t len);
sds    sdscat(sds s, char *t);
sds    sdscatlen(sds s, char *t, size_t len);
sds    sdscatprintf(sds s, const char *fmt, ...);
sds    sdstrim(sds s, const char *cset);
sds    sdsrange(sds s, long start, long end);
void   sdsupdatelen(sds s);
int    sdscmp(const sds s1, const sds s2);
sds   *sdssplitlen(sds s, int len, char *sep, int seplen, int *count);
void   sdstolower(sds s);
void   sdstoupper(sds s);

#endif /* SDS_H */
