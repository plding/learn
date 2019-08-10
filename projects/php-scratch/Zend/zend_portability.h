#ifndef ZEND_PORTABILITY_H
#define ZEND_PORTABILITY_H

#ifdef __cplusplus
#define BEGIN_EXTERN_C() extern "C" {
#define END_EXTERN_C() }
#else
#define BEGIN_EXTERN_C()
#define END_EXTERN_C()
#endif

#endif /* ZEND_PORTABILITY_H */
