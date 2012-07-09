#include <stdlib.h>

#include "mm.h"
enum POOL_TYPE {
	POOL_STRING = 0,
	POOL_MAX_SIZE,
};

static apr_pool_t* pools[POOL_MAX_SIZE] = {0};

void init_mm()
{
	for (int i = 0; i < POOL_MAX_SIZE; ++i) {
		apr_pool_create(&pools[i], NULL);
		if (pools[i] == NULL) {
			log_print("init memory pool fail");
			exit(1);
		}
	}
}

apr_pool_t* new_string_pool()
{
	apr_pool_t* pool = NULL;
	apr_pool_create(&pool, pools[POOL_STRING]);
	return pool;
}

void engine_mm_free(void* ptr)
{
	free(ptr);
}
