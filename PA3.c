#include "types.h"
#include "user.h"
#include "syscall.h"
#include "mmu.h"

int main(int argc, char *argv[]) {
	int* test = (int*) malloc(sizeof(int));
	*test = 10;
	int pdxval;	
	if ((pdxval = uv2p(test))) {
		printf(1,"Virtual address is: %p\n",test);
		printf(1,"Physical address is: %p\n",pdxval);

	} else {
		printf(1, "Error\n");
	}
	exit();
}
