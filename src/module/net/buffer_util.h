/*
 * buffer_util.h
 *
 *  Created on: 2012-7-5
 *      Author: AzureSky
 */

#ifndef BUFFER_UTIL_H_
#define BUFFER_UTIL_H_

#include <event2/buffer.h>

void evbuffer_write_to_file(const char* file, struct evbuffer* buf, const char* mode);


#endif /* BUFFER_UTIL_H_ */
