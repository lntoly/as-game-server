#include "module/os/os.h"
//#include "program/httpd/httpd.h"
#include "program/echo/echo.h"

int main(void) {
	init_os();

	init_echo();
	close_echo();

	close_os();
	return 0;
}
