#ifndef ZMALLOC_H
#define ZMALLOC_H

void *zmalloc(size_t size);
void *zrealloc(void *ptr, size_t size);
void zfree(void *ptr);
size_t zmalloc_used_memory(void);

#endif /* ZMALLOC_H */
