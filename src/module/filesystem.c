#include <stdlib.h>
#include <apr_file_io.h>
#include "filesystem.h"

int make_dir(const char* path)
{
	apr_pool_t* pool = NULL;
	apr_pool_create(&pool, NULL);
	apr_status_t rv = apr_dir_make(path, APR_OS_DEFAULT, pool);
	apr_pool_destroy(pool);

    if (APR_SUCCESS != rv && !APR_STATUS_IS_EEXIST(rv)) {
    	return 0;
    }
    else return 1;
}
