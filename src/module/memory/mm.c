#include <stdlib.h>

#include "mm.h"

void init_mm()
{
}

apr_pool_t* new_pool()
{
	apr_pool_t* pool = NULL;
	apr_pool_create(&pool, NULL);
	return pool;
}

void engine_mm_free(void* ptr)
{
	free(ptr);
}
