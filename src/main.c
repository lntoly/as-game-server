#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "module/init_engine.h"
#include "program/httpd/httpd.h"
#include "program/echo/echo.h"
#include "program/test_server/test_server.h"

void show_help()
{
	printf("usage:\n"
			"  -e start echo server\n"
			"  -h start http server\n"
			"  -s start test server\n");
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		show_help();
		return 0;
	}

	char* pro = argv[1];
	if (strlen(pro) < 2 || pro[0] != '-') {
		show_help();
		return 0;
	}

	void (*start_fun)(int, char**);
	void (*end_fun)();

	start_fun = end_fun = NULL;

	switch (pro[1]) {
		case 'h': {
			start_fun = init_httpd;
			end_fun = close_httpd;
		} break;

		case 'e': {
			start_fun = init_echo;
			end_fun = close_echo;
		} break;

		case 's': {
			start_fun = init_test_server;
			end_fun = close_test_server;
		} break;

		default: show_help(); return 0;
	}

	if (start_fun == NULL || end_fun == NULL) {
		show_help();
		return 0;
	}

	init_engine();

	(*start_fun)(argc, argv);
	(*end_fun)();

	close_engine();
	return 0;
}
