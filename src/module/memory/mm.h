/*
 * mm.h
 *
 *  Created on: 2012-7-6
 *      Author: Administrator
 */

#ifndef MM_H_
#define MM_H_

#include <apr_pools.h>

void init_mm();

apr_pool_t* new_string_pool();

void engine_mm_free(void*);

#define E_FREE engine_mm_free

#endif /* MM_H_ */
