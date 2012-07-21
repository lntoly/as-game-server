#include "os.h"
#ifdef WIN32
	#include <windows.h>
#endif

#include <event2/event.h>
#include <apr_general.h>
#include "module/log.h"
#include "module/memory.h"

// check libevent
#if !defined(LIBEVENT_VERSION_NUMBER) || LIBEVENT_VERSION_NUMBER < 0x02001300
#error "This version of Libevent is not supported; Get 2.0.13 or later."
#endif

void init_os()
{
#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
#endif

	apr_initialize();
	init_mm();

	init_log();
}

void close_os()
{
	apr_terminate();
}
