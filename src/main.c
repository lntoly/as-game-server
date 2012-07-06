#include "os/os.h"
#include "program/httpd/httpd.h"

int main(void) {
	init_os();

	init_httpd();
	close_httpd();

	return 0;
}
