#include "types.h"
#include "stat.h"
#include "user.h"

enum processState { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct proc {
  enum processState state;
  int pid;            
	int sz;
  char name[16];         
};

int
main(int argc, char *argv[]){  
  int pses = 15;
	struct proc ptable[pses];
  struct proc *p; 
	int check;

  check = procstate(15*sizeof(struct proc),&ptable);
  if(check !=0)
    printf(1,"Error getting ptable");
  
  p = &ptable[0];
  printf(1, "NAME\tSTATE\t\tPID\tMEMORY\n");
  while(p != &ptable[pses-1] && p->state != UNUSED){
  	printf(1,"%s\t", p->name);
  	switch(p->state){
  	case UNUSED:
  		printf(1,"%s ", "UNUSED");
  		break;
  	case EMBRYO:
  		printf(1,"%s", "EMBRYO");
  		break;
  	case SLEEPING:
  		printf(1,"%s", "SLEEPING");
  		break;
  	case RUNNABLE:
  		printf(1,"%s", "RUNNABLE");
  		break;
  	case RUNNING:
  		printf(1,"%s", "RUNNING");
  		break;
  	case ZOMBIE:
  		printf(1,"%s", "ZOMBIE");
  		break;
  	} 
		printf(1,"\t\t%d\t%d\n",p->pid,p->sz);
  	p++;
  }
	exit();
}
