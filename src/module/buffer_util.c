#include <stdio.h>
#include "buffer_util.h"

void evbuffer_write_to_file(const char* file, struct evbuffer* buf, const char* mode)
{
	FILE* fd = fopen(file, mode);
	if (fd == NULL) {
		goto done;
	}

	evbuffer_lock(buf);
	int len = evbuffer_get_length(buf);
	unsigned char* file_buf = evbuffer_pullup(buf, len);
	if (file_buf == NULL) {
		goto done;
	}

	fwrite(file_buf, len, 1, fd);

done:
	evbuffer_unlock(buf);
	if (fd) {
		fflush(fd);
		fclose(fd);
	}
}
