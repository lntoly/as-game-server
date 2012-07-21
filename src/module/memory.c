#include <stdlib.h>
#include <apr_pools.h>

#include "memory.h"

void init_mm()
{
}

inline void engine_mm_free(void* ptr)
{
	free(ptr);
}

inline struct apr_pool_t* pool_new()
{
	apr_pool_t* pool = NULL;
	apr_pool_create(&pool, NULL);
	return pool;
}

inline void pool_free(struct apr_pool_t* pool)
{
	apr_pool_destroy(pool);
}

inline void* pool_palloc(struct apr_pool_t* pool, int size)
{
	return apr_palloc(pool, size);
}
