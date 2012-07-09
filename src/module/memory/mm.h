#ifndef MM_H_
#define MM_H_

struct apr_pool_t;
typedef struct apr_pool_t mm_pool_t;

void init_mm();

mm_pool_t* pool_new();
void pool_free(mm_pool_t*);
void* pool_palloc(mm_pool_t*, int);

void engine_mm_free(void*);

#define E_FREE engine_mm_free

#endif /* MM_H_ */
