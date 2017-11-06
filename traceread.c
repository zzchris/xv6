#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[]) {
	int fd = (int)argv[1];
	void *buf = argv[2];
	int count = (int)argv[3];
	
		
	if (read(fd, buf, count) == - 1) {
		printf(1,"Error from traceread!\n");
	} else {
		printf(1,"No errors from traceread!\n");
	}
	exit();
}
