#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

extern struct proc* procstate_proc(void);
int sys_procstate(void) {
  char *s;
  struct proc *p = '\0';
  char *buf;
 	int size;
  
  if (argint(0, &size) <0){
    return -1;
  }
  if (argptr(1, &buf,size) <0){
    return -1;
  }
  
  s = buf;
  p = procstate_proc();
  
  while(buf + size > s && p->state != UNUSED){
    *(int *)s = p->state;
    s+=4;
		*(int *)s = p-> pid;
    s+=4;
    *(int *)s = p->sz;
		s+=4;
    memmove(s,p->name,16);
    s+=16;
    p++;
  } 
  return 0;	
}
int
sys_uv2p(void) {
	int va;
	if (argint(0,&va) < 0) {
		return -1;
	}

	pde_t *curprocPGDIR, *curprocPGTAB, *curprocPDE;
	//get page directory
	curprocPGDIR = myproc()->pgdir;

	//get process's PDE
	curprocPDE = &curprocPGDIR[PDX(va)];
	if (*curprocPDE & PTE_P) {
		//get page table
		curprocPGTAB = (pte_t*)P2V(PTE_ADDR(*curprocPDE));
		} else {
			cprintf("Page table not found\n");
			return -1;
	}
	
	//calculate offset
	unsigned int offset = (uint)va & 0xFFF;
	pte_t *curprocPTE;
	//get page table entry
	curprocPTE = &curprocPGTAB[PTX(va)];
	//physical address = pte + offset
	return (PTE_ADDR(*curprocPTE)+offset);
}
