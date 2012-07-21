#include "module/init_engine.h"
#include "program/httpd/httpd.h"
#include "program/echo/echo.h"

int main(void) {
	init_engine();

	//init_echo();
	//close_echo();
	init_httpd();
	close_httpd();

	close_engine();
	return 0;
}
