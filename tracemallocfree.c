#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[]) {
	int *pointer = malloc(sizeof(int));
	printf(1,"Pointer address = %d\n", pointer);
	free(pointer);
	exit();
}
