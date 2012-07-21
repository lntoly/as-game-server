#ifndef MEMORY_H_
#define MEMORY_H_

struct apr_pool_t;

void init_mm();

struct apr_pool_t* pool_new();
void pool_free(struct apr_pool_t*);
void* pool_palloc(struct apr_pool_t*, int);

void engine_mm_free(void*);

#define E_FREE engine_mm_free

#endif /* MEMORY_H_ */
