#include "types.h"
#include "user.h"
#include "syscall.h"
#include "mmu.h"

int main(int argc, char *argv[]) {
	int* dataA = (int*) malloc(4 * sizeof(int));
	dataA[0] = 10;
  dataA[1] = 4;	
  dataA[2] = 3;
  dataA[3] = 2;

	char dataB[2];
	dataB[0] = 'a';
	dataB[1] = 'b';
	dataB[2] = 'p';
	
	int pdxval;
	int i,a;
	for (i =0; i < 4; i++ ) {	
		if ((pdxval = uv2p(&dataA[i]))) {
			printf(1,"Virtual address %d is: %p\n",i,&dataA[i]);
			printf(1,"Physical address %d is: %p\n",i,pdxval);
		} else {
			printf(1, "Error\n");
		}
	}
 for (a =0; a<3; a++) {
 	if ((pdxval = uv2p(&dataB[a]))) {
			printf(1,"Virtual address %d is: %p\n",a,&dataB[a]);
			printf(1,"Physical address %d is: %p\n",a,pdxval);
		} else {
			printf(1, "Error\n");
		}
	}	
 free(dataA);
	exit();
}
