#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "module/net/buffer_util.h"

static char* _make_datetime()
{
	static char buffer[32] = {0};
	static time_t last_time = 0;

	time_t now = time(NULL);
	if (last_time != now) {
		struct tm* timeinfo;
		timeinfo = localtime(&now);
		strftime(buffer ,32,"%Y-%m-%d %X", timeinfo);
		last_time = now;
	}

	return buffer;
}

static void make_datetime(struct evbuffer* buf)
{
	evbuffer_add_printf(buf, "[%s] ", _make_datetime());
}

void log_print(const char* fmt, ...)
{
	printf("[%s] ", _make_datetime());
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

void log_file(const char* file, const char* fmt, ...)
{
	struct evbuffer* buf = evbuffer_new();
	if (buf == NULL) return;

	va_list ap;
	va_start(ap, fmt);
	evbuffer_add_vprintf(buf, fmt, ap);
	va_end(ap);
	evbuffer_add_printf(buf, "\n");

	evbuffer_write_to_file(file, buf, "a+");

	evbuffer_free(buf);
}

void log_file_with_time(const char* file, const char* fmt, ...)
{
	struct evbuffer* buf = evbuffer_new();
	if (buf == NULL) return;

	make_datetime(buf);
	va_list ap;
	va_start(ap, fmt);
	evbuffer_add_vprintf(buf, fmt, ap);
	va_end(ap);
	evbuffer_add_printf(buf, "\n");

	evbuffer_write_to_file(file, buf, "a+");

	evbuffer_free(buf);
}
