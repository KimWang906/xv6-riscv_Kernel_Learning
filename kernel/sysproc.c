#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()-> pid;
}

uint64
sys_fork(int pid)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
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

uint64
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

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_getcwd(void) {
    char *p;
    int n;
    struct proc *curproc = myproc();

    if(argint(1, &n) < 0 || argptr(0, &p, n) < 0)
       return -1;

    return name_for_inode(p, n, curproc->cwd);
}

// struct proc *p; // proc 구조체에 접근하여 spinlock을 사용하기 위한 구조체 포인터 p

// uint64
// sys_setpgid(int pid, int pgid) // 해당 함수는 pgid 값을 변경하는 함수입니다.
// {

//   if(pid != pgid)
//   {

//   }

//   if(pid == 0) // 자식 프로세스일 경우
//   {
//     acquire(&p->lock); // lock을 획득합니다.
//     // Critical section
//     myproc()-> pgid = pgid; // System Call을 호출한 process group id를 변경합니다.
//     release(&p->lock); // lock을 반환합니다.
//     return 0; // 변경에 성공할 경우, 0을 return 합니다.

//   }else if(pgid == 0) //
//   {
//     acquire(&p->lock); // lock을 획득합니다.
//     pgid = pid; // Process group id를 pid와 동일하게 변경합니다.
//     release(&p->lock); // lock을 반환합니다.
//     return 0; // 변경에 성공할 경우, 0을 반환합니다.
//   }else if(pid == pgid)
//   {
//     acquire(&p->lock); // locked

//   }
  
  
//   return -1; // 변경에 실패했을 경우, -1을 반환합니다.
// }

// uint64
// sys_getpgid(int pid) // 해당 함수는 pgid를 반환하는 함수입니다.
// { 
//   uint pgid; // pgid를 return 할 때 필요한 변수 pgid
//   if(pid == 0) // 자식 프로세스일 경우
//   {
//     acquire(&p->lock); // lock을 획득합니다.
//     pgid = myproc()-> pgid; // 현재 Process의 pgid를 받아옵니다.
//     release(&p->lock); // lock을 반환합니다.
//     return pgid; // 현재 Process의 group id를 반환합니다.

//   }else return -1; // 변경에 실패했을 경우, -1을 반환합니다.
// }
