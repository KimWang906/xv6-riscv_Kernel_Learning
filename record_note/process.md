# OSTEP 정리

## Process

### 정의

Process는 실행 중인 프로그램입니다.

### 설명

해당 프로그램은 디스크 상에 존재하며 실행을 위한 명령어와 정적 데이터의 묶음입니다.  
이 명령어와 데이터 묶음을 읽고 실행하여 프로그램에 생명을 불어넣는 것이 운영체제입니다.  
  
사용자는 하나 이상의 프로그램을 동시에 실행시키기를 원합니다.  
예를 들어, 웹 브라우저, 메일 프로그램, 게임, 음악 플레이어 등을 실행하는 컴퓨터를 생각해 보면  
컴퓨터들은 동시에 수십 혹은 수백 개의 프로세스를 실행하는 것처럼 보입니다.  
여러 프로그램을 동시에 실행할 수 있으면, 시스템을 쉽게 사용할 수 있고,  
사용자는 사용 가능한 CPU가 있는지 신경쓰지 않고 그저 프로그램만 실행시키면 됩니다.  
  
### 1번째 목표  
  
CPU가 여러 개 존재한다는 환상을 제공하는 방법  
적은 개수의 CPU 밖에 없더라도, 운영체제는 어떻게 거의 무한개에 가까운 CPU가 있는 듯한 환상을 만드는 방법  

## 시분할(time sharing)

운영체제는 CPU를 가상화하여 이러한 환상을 만들어 냅니다.  
하나의 프로세스를 실행하고, 얼마 후 중단시키고 다른 프로세스를 실행하는 작업을 반복하면서 실제 하나  
또는 소수의 CPU로 여러 개의 가상 CPU가 존재하는 듯한 환상을 만들어 냅니다.  
**시분할(time sharing)** 이라 불리는 이 기법은 **원하는 수 만큼의 프로세스를 동시에 실행할 수 있게 합니다.**  
그러나 **시분할 기법**은 CPU를 공유하기 때문에, **각 프로세스의 성능은 낮아지는 단점**이 있습니다.  
  
**시분할**은 자원 공유를 운영체제가 사용하는 가장 기본 기법 중 하나입니다.  
한 개체가 잠깐 자원을 사용한 후, 다른 개체가 또 잠깐 자원을 사용하고,  
그 다음 개체가 사용하면서 이 자원(CPU 또는 네트워크 링크 등)을 많은 개체들이 공유합니다.  
시분할과 자연스럽게 대응되는 개념은 **공간 분할(space sharing)**이 될 것입니다.  
  
공간 분할은 개체에게 공간을 분할해 주고, 그 예로는 공간 분할의 예로 디스크가 있습니다.  
디스크는 **자연스럽게 공간 분할할 수 있는 자원**으로,  
블럭이 하나의 파일에 할당되면 파일을 삭제하기 전에는 다른 파일이 할당될 가능성이 낮습니다.  

## 운영체제의 지능

운영체제의 지능은 **정책(policy)** 의 형태로 표현되고,  
정책은 운영체제 내에서 어떤 결정을 내리기 위한 알고리즘입니다.  
  
운영체제의 **스케줄링 정책(scheduling policy)** 이 이러한 결정을 내립니다.  
그리고 이러한 결정을 내리기 위하여 스케줄링 정책은 과거 정보(직전 1분 동안 어떤 프로그램이 자주 실행되었는지),  
워크로드에 관한 지식(어떤 유형의 프로그램들이 실행되었는지),  
및 성능 측정 결과 (시스템이 대화 성능 혹은 처리량을 높이려 하는지)를 이용합니다.  

## 개념

만약 특정 순간의 프로세스를 간단하게 표현하려면, 실행되는 동안 접근했거나 영향을 받은 자원의 목록을 작성하면 됩니다.  
프로세스의 구성 요소를 이해하기 위해서는 먼저 **하드웨어 상태(machine state)** 를 이해해야 하는데  
프로그램이 실행되는 동안 하드웨어 상태를 읽거나 갱신할 수 있습니다.  
  
이때 가장 중요한 하드웨어 구성 요소는 무엇일까요?  
  
프로세스의 하드웨어 상태 중 가장 중요한 구성 요소는 메모리이고, 이곳에는 명령어가 저장됩니다.  
또한 실행 프로그램이 읽고 쓰는 데이터 역시 메모리에 저장됩니다.  
프로세스가 접근할 수 있는 **메모리**(**주소 공간(address space)** 이라 불림)는 프로세스를 구성하는 요소입니다.  
레지스터도 프로세스의 하드웨어 상태를 구성하는 요소 중 하나이고 많은 명령어들이 레지스터를 직접 읽거나 갱신합니다.  
  
또한 프로세스를 실행할 때 레지스터도 빠질 수 없습니다.  
프로세스의 하드웨어 상태를 구성하는 레지스터 중에 특별한 레지스터들이 존재합니다.  
  
**프로그램 카운터(program counter, PC)** 는 프로그램의 어느 명령어가 실행 중인지를 알려주고  
**명령어 포인터(instruction pointer, IP)**  라고도 불립니다.  
**스택 포인터(stack pointer)** 와 **프레임 포인터(frame pointer)** 는  
함수의 변수와 리턴 주소를 저장하는 스택을 관리할 때 사용하는 레지스터입니다.  
프로그램은 영구 **저장장치 (persistent storage)** 에 접근하기도 합니다.  
이 입출력 정보는 프로세스가 현재 열어 놓은 파일 목록을 가지고 있습니다.  

* **생성 (Create)**: 운영체제는 새로운 프로세스를 생성할 수 있는 방법을 제공해야 합니다.
  * 쉘에 명령어를 입력하거나, 응용 프로그램의 아이콘을 클릭하여 프로그램을 실행시키면, 운영체제는 새로운 프로세스를 생성합니다.
  
* **제거 (Destroy)**: 프로세스 생성 인터페이스를 제공하는 것처럼 운영체제는 프로세스를 강제로 제거할 수 있는 인터페이스를 제공해야 합니다.
  * 물론, 많은 프로세스는 실행되고 할 일을 다하면 스스로 종료합니다.
  * 그러나 프로세스가 스스로 종료하지 않으면 사용자는 그 프로세스를 제거하길 원할 것이고, 필요없는 프로세스를 중단시키는 API는 매우 유용합니다.
  
* **대기 (Wait)**: 때로는 어떤 프로세스의 실행 중지를 기다릴 필요가 있기 때문에 여러 종류의 대기 인터페이스가 제공됩니다.
  
* **각종 제어 (Miscellaneous Control)**: 프로세스의 제거, 대기 이외에, 여러 가지 제어 기능들이 제공됩니다.
  * 예를 들어, 대부분의 운영체제는 프로세스를 일시정지하거나 재개 (일시정지되었던 프로세스의 실행을 다시 시작)하는 기능을 제공합니다.
  
* **상태 (Status)**: 프로세스 상태 정보를 얻어내는 인터페이스도 제공됩니다.
  * 상태 정보에는 얼마 동안 실행되었는지 또는 프로세스가 어떤 상태에 있는지 등이 포함됩니다.

## 프로세스 상태

상태의 개념은 초기 컴퓨터 시스템에서 등장하였습니다.  

프로세스 상태를 단순화하면 다음 세 상태 중 하나에 존재할 수 있습니다.  

<p align="center"><img src="/readme_img/process_state.png"></p>

* **실행 (Running)**: 실행 상태에서 프로세스는 프로세서에서 실행 중입니다.
  * 즉, 프로세스는 명령어를 실행하고 있습니다.
  
* **준비 (Ready)**: 준비 상태에서 프로세스는 실행할 준비가 되어 있지만 운영체제가 다른 프로세스를 실행하고 있는 등의 이유로 대기 중입니다.
  
* **대기 (Blocked)**: 프로세스가 다른 사건을 기다리는 동안 프로세스의 수행을 중단시키는 연산입니다.
  * 흔한 예 : 프로세스가 디스크에 대한 입출력 요청을 하였을 때
  * 프로세스는 입출력이 완료될 때까지 대기 상태가 되고, 다른 프로세스가 실행상태로 될 수 있습니다.

## 자료구조

운영체제도 일종의 프로그램이고, 다른 프로그램들과 같이 다양한 정보를 유지하기 위한 자료 구조를 가지고 있습니다.  
예를 들어, 프로세스 상태를 파악하기 위해 준비 상태의 프로세스들을 위한 프로세스 **리스트(process list)** 와 같은 자료 구조를 유지합니다.  
또한, 어느 프로세스가 실행 중인지를 파악하기 위한 부가적인 자료 구조도 유지합니다.  
운영체제는 또 대기 상태인 프로세스도 파악해야 합니다.  
입출력 요청이 완료되면 운영체제는 적절한 프로세스를 깨워 준비 상태로 다시 전이시킬 수 있어야 합니다.

```//
// 프로세스를 중단하고 이후에 재개하기 위해
// xv6가 저장하고 복원하는 레지스터
struct context {
  uint64 ra;
  uint64 sp;

  // callee-saved
  uint64 s0;
  uint64 s1;
  uint64 s2;
  uint64 s3;
  uint64 s4;
  uint64 s5;
  uint64 s6;
  uint64 s7;
  uint64 s8;
  uint64 s9;
  uint64 s10;
  uint64 s11;
};

// 가능한 프로세스 상태
/*
    아래 코드에서 실행, 준비, 대기 외에 다른 상태들이 존재하는 것을 볼 수 있는데, 
    초기(initial) 상태(프로세스가 생성되는 동안에는 초기 상태에 머무는 것)를 가지는 시스템도 있습니다.  
    프로세스는 종료되었지만 메모리에 남아있는 상태인 최종(inal)상태도 있습니다.
    (Unix-기반 시스템에서 이 상태는 좀비(zombie) 상태라고 불립니다)  
    이 상태는 프로세스가 성공적으로 실행했는지를 다른 프로세스(보통은 부모(parent)프로세스)가 검사하는 데 유용합니다.  
    이를 위하여 최종 상태를 활용합니다. (Unix-기반 시스템에서는 프로세스가 성공적으로 종료되었으면 0을, 그렇지 않으면 0이 아닌 값을 반환합니다)  
    부모 프로세스는 자식 프로세스의 종료를 대기하는 System Call을 호출(예, wait())하고, 
    해당 호출은 종료된 프로세스와 관련된 자원들을 정리할 수 있다고 운영체제에 알리는 역할도 합니다.
*/
enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct proc {
  struct spinlock lock;

  // p->lock must be held when using these:
  enum procstate state;        // Process state(프로세스의 상태)
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  int xstate;                  // Exit status to be returned to parent's wait
  int pid;                    // Process ID
  int pgid;                   // Process Group ID(8 / 1 Update)
  // wait_lock must be held when using this:
  struct proc *parent;         // Parent process(부모 프로세스)

  // these are private to the process, so p->lock need not be held.
  uint64 kstack;               // Virtual address of kernel stack(이 프로세스의 커널 스택의 바닥주소)
  uint64 sz;                   // Size of process memory (bytes)(프로세스 메모리의 크기)
  pagetable_t pagetable;       // User page table
  struct trapframe *trapframe; // data page for trampoline.S
  struct context context;      // swtch() here to run process
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory(현재 디렉터리)
  char name[16];               // Process name (debugging)
};
```

위 코드는 xv6 커널에서 각 프로세스를 추적하기 위해 운영체제가 필요로 하는 정보를 보이고 있습니다.  
Linux, Mac OS X, 또는 Windows 같은 운영체제들도 이와 비슷한 프로세스 구조를 가지고 있고, 찾아 보면 훨씬 복잡하다는 것을 알 수 있습니다.
  
우리는 위 코드를 통해 운영체제가 관리하는 있는 프로세스 정보를 알 수 있습니다.
  
**레지스터 문맥(register context)** 자료 구조는 프로세스가 중단되었을 때 해당 프로세스의 레지스터값들을 저장합니다.  
이 레지스터값들을 복원하여 (예, 해당 값을 실제 물리 레지스터에 다시 저장함으로써) 운영체제는 프로세스 실행을 재개합니다.  
**문맥 교환(context switch)** 이라고 알려진 이 기법에 관해서 추후 자세히 다루기로 합니다.

## Process API

### 주제(프로세스를 생성하고 제어하는 방법)

이번 회차의 주제는 Unix 시스템의 프로세스 생성에 관해 논의하는 것입니다.

### 2번째 목표

프로세스를 생성하고 제어하려면 운영체제가 어떤 인터페이스를 제공해야 하나요? 와  
유용하고 편하게 사용하기 위해서 이 인터페이스는 어떻게 설계되어야 하나요? 라는 질문에 대한 해답을 찾아야 합니다.

## fork() System Call

프로세스 생성에 **fork()** System Call이 사용됩니다.  
미리 경고하자면, 해당 System Call이 사용할 System Call 중에서 가장 이해하기 힘든 System Call이 될 것입니다.

아래 코드에서 해당 System Call에 대해 확인할 수 있습니다.

## Example Code - fork()

```code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n ", (int) getpid());

  int rc = fork();

  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n ");
    exit(1);

  } else if (rc == 0) { // 자식(새 프로세스)
    printf("hello, I am child (pid:%d)\n ", (int) getpid());

  } else { // 부모 프로세스는 main의 경로를 따라 실행됩니다.
    printf("hello, I am parent of %d (pid:%d)\n ",
    rc, (int) getpid());
  }

  return 0;
}
```

## fork() Result - 1

  hello world (pid:46316)  
   hello, I am parent of 46320 (pid:46316)  
   hello, I am child (pid:46320)  

## fork() Result - 2(Other)

  hello world (pid:46316)  
   hello, I am child (pid:46320)  
   hello, I am parent of 46320 (pid:46316)  

### Example Code - fork() Code 분석

실행이 시작될 때 프로세스는 "hello world ..." 메시지를 출력합니다.  
이 메시지에는 **PID**로도 알려진 프로세스 **식별자(process identiier)** 가 포함됩니다.  
이 프로세스는 46316이라는 **PID**를 가집니다.  
Unix 시스템에서 **PID**는 프로세스의 실행이나 중단과 같이 특정 프로세스를 대상으로 작업을 해야 할 경우 프로세스를 지칭하기 위해 사용됩니다.  
  
하지만 재미있는 부분은 여기서부터 시작되는데요,  
  
프로세스는 **fork()** System Call을 호출하고, 운영체제는 프로세스 생성을 위해 이 System Call을 제공합니다.  
그러나 어딘가 이상한 부분이 있습니다. 바로 생성된 프로세스가 호출한 프로세스의 복사본이라는 것입니다.  
**fork()** 호출 직후를 살펴보겠습니다.  
운영체제 입장에서 보면 프로그램이 2개가 존재하고, 두 프로세스가 모두 **fork()** 에서 리턴하기 직전입니다.  
새로 생성된 프로세스는 (일반적으로 자식 프로세스, 생성한 프로세스는 부모 프로세스라 불립니다)  
**main()** 함수 첫 부분부터 시작하지 않았다는 것을 알 수 있습니다. ("hello, world" 메시지가 한 번만 출력되었다는 것에 유의하기 바랍니다)  
자식 프로세스는 **fork()** 를 호출하면서부터 시작되었습니다.  
자식 프로세스는 부모 프로세스와 완전히 동일하지는 않습니다.  
자식 프로세스는 자신의 **주소 공간**, 자신의 **레지스터**, 자신의 **PC(Program Counter)** 값을 갖습니다.  
매우 중요한 차이점이 있고, 이 점은 아무리 강조해도 지나치지 않습니다.  
**fork()** System Call의 반환 값이 서로 다릅니다.  
**fork()** 로 부터 부모 프로세스는 생성된 자식 프로세스의 PID를 반환받고, 자식 프로세스는 0을 반환받습니다.  
이 반환 값의 차이로 인해, 위 코드와 같이 부모와 자식 프로세스가 서로 다른 코드를 실행하는 프로그램을 쉽게 작성할 수 있습니다.  
  
이 프로그램의 출력 결과가 항상 동일하지는 않습니다.  
  
단일 CPU 시스템에서 이 프로그램을 실행하면, 프로세스가 생성되는 시점에는 2개 (부모와 자식) 프로세스 중 하나가 실행됩니다.  
[위의 출력 예](#result---1)에서는 부모 프로세스 실행 후에 자식 프로세스가 실행되었습니다.  
[바로 아래 결과 예](#result---2other)에서 볼 수 있는 바와 같이, 그 반대 경우도 발생할 수 있습니다.  

**CPU 스케줄러(scheduler)** 는 실행할 프로세스를 선택합니다.  
스케줄러에 관해서는 조만간 자세히 이야기할 것입니다.  
스케줄러의 동작은 일반적으로 상당히 복잡하고 상황에 따라 다른 선택이 이루어지기 때문에,  
어느 프로세스가 먼저 실행된다라고 단정하는 것은 매우 어렵습니다.  
이 **비결정성(nondeterminism)** 으로 인해 **멀티 쓰레드 프로그램** 실행 시 다양한 문제가 발생합니다.

## wait() System Call

이제까지 메시지를 출력하는 자식 프로세스를 만들어 보았습니다.  
부모 프로세스가 자식 프로세스의 종료를 대기해야 하는 경우도 발생할 수 있습니다.  
이러한 작업을 위해 **wait()** System Call이 (혹은 더 많은 기능을 가진 **waitpid()**)있습니다.  

자세한 것은 아래 코드를 보겠습니다.

## Example Code - fork() & wait()

```code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n ", (int) getpid());
  int rc = fork();

  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n ");
    exit(1);

  } else if (rc == 0) { // 자식(새 프로세스)
    printf("hello, I am child (pid:%d)\n ", (int) getpid());

  } else { // 부모 프로세스는 main의 경로를 따라 실행됩니다.
    int wc = wait(NULL);
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n ",
    rc, wc, (int) getpid());

  }

  return 0;
}
```

## fork() & wait() Result

  hello world (pid:50480)  
   hello, I am child (pid:50486)  
    hello, I am parent of 50486 (wc:50486) (pid:50480)  

### Example Code - fork() & wait() Code 분석

[위 코드](#example-code---fork--wait)에서 부모 프로세스는 **wait()** System Call을 호출하여 자식 프로세스 종료 시점까지 자신의 실행을 잠시 중지시킵니다.  
자식 프로세스가 종료되면 **wait()** 은 리턴합니다.

**wait()** 호출을 [위 코드](#example-code---fork--wait) 같이 코드에 추가하면 프로그램은 항상 동일한 결과를 출력합니다.

[출력 결과](#fork--wait-result)를 보면 이 코드에서는 항상 자식 프로세스가 먼저 출력을 수행한다는 것을 알 수 있습니다.  
왜 그럴까요? 자식 프로세스가 부모 프로세스보다 먼저 실행되면 당연히 자식 프로세스가 먼저 출력됩니다.  
부모 프로세스가 먼저 실행되면 곧바로 **wait()** 을 호출합니다.  
이 System Call은 자식 프로세스가 종료될 때까지 리턴하지 않습니다.  
부모가 먼저 실행되더라도 자식 종료 후 **wait()** 이 리턴합니다.  
그런 후 부모 프로세스가 출력합니다.  

## exec() System Call

이 System Call은 자기 자신이 아닌 다른 프로그램을 실행해야 할 때 사용합니다.  
**exec()** System Call에는 6가지 변형이 존재합니다.  
**execl()**, **execle()**, **execlp()**, **execv()**, **execvp()**, **execve()** 가 그것입니다.  
**fork()** System Call은 자신의 복사본을 생성하여 실행합니다.  
자신의 복사본이 아닌 다른 프로그램을 실행해야 할 경우에는 바로 **exec()** System Call이 그 일을 하고,  
[아래 코드](#example-code---fork--wait--exec)는 **exec()** 를 사용한 예제입니다.  

## Example Code - fork() & wait() & exec()

```code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int
main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n ", (int) getpid());

  int rc = fork();

  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n ");
    exit(1);
  
  } else if (rc == 0) { // 자식(새 프로세스)
    printf("hello, I am child (pid:%d)\n ", (int) getpid());
    char *myargs[3];
    myargs[0] = strdup("wc "); // 프로그램: "wc" (단어 세기)
    myargs[1] = strdup("p3.c "); // 인자: 단어를 셀 파일
    myargs[2] = NULL; // 배열의 끝 표시
    execvp(myargs[0], myargs); // "wc" 실행
    printf("this shouldn't print out ");
  
  } else { /// 부모 프로세스는 main의 경로를 따라 실행됩니다.
    int wc = wait(NULL);
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n ",
    rc, wc, (int) getpid());
  }

  return 0;
}
```

## fork() & wait() & exec() Result

  hello world (pid:56900)  
   hello, I am child (pid:56905)  
   this shouldn't print out  hello, I am parent of 56905 (wc:56905) (pid:56900)  

### Example Code - fork() & wait() & exec() Code 분석

자식 프로세스는 **wc** 프로그램을 실행하기 위해 **execvp()** System Call을 호출합니다.  
**wc** 프로그램은 단어의 개수를 세는 프로그램입니다.  
사실 예제 프로그램은 자신의 소스 파일을 인자로 하여 **wc**를 실행하고  
소스 코드의 행 개수, 단어의 개수, 바이트의 개수를 알려 줍니다.  

사실 **fork()** System Call만큼 **exec()** System Call도 이해하기 어렵습니다.  
**exec()** System Call은 다음과 같은 과정으로 수행됩니다.  
실행 파일의 이름과 (예, **wc**) 약간의 인자가 (예, [자기 자신의 파일](#example-code---fork--wait--exec)) 주어지면  
해당 실행 파일의 코드와 정적 데이터를 읽어 들여 현재 실행 중인 프로세스의 코드 세그멘트와 정적 데이터 부분을 덮어 씁니다.  
힙과 스택 및 프로그램 다른 주소 공간들로 새로운 프로그램의 실행을 위해 다시 초기화됩니다.  
그런 다음 운영체제는 프로세스의 argv와 같은 인자를 전달하여 프로그램을 실행시킵니다.  
새로운 프로세스를 생성하지는 않고, 현재 실행 중인 프로그램을 다른 실행 중인 프로그램으로 대체하는 것입니다.  
자식 프로세스가 **exec()**을 호출한 후에는 실행했던 파일은 전혀 실행되지 않은 것처럼 보입니다.  
**exec()** System Call이 성공하게 되면 실행했던 파일은 절대로 리턴하지 않습니다.  

### 왜 이런 API를?

여기서 이런 의문이 생길 수 있습니다.  
새로운 프로세스를 생성하는 간단한 작업 같은데, 왜 이런 이상한 인터페이스를 사용할까요?  
  
Unix의 쉘을 구현하기 위해서는 **fork()**와 **exec()**을 분리해야 합니다.  
그래야만 쉘이 **fork()**를 호출하고 **exec()**를 호출하기 전에 코드를 실행할 수 있습니다.  
이때 실행하는 코드에서 프로그램의 환경을 설정하고, 다양한 기능을 준비합니다.  
쉘은 단순한 사용자 프로그램이며 프롬프트를 표시하고 사용자가 무언가 입력하기를 기다립니다.  
그리고 명령어를 입력합니다.(예, 실행 프로그램의 이름과 필요한 인자)  
대부분의 경우 쉘은 파일 시스템에서 실행 파일의 위치를 찾고 명령어를 실행하기 위하여 **fork()**를 호출하여 새로운 자식 프로세스를 만듭니다.  
그런 후 **exec()**의 변형 중 하나를 호출하여 프로그램을 실행시킨 후 **wait()**를 호출하여 명령어가 끝나기를 기다립니다.  
자식 프로세스가 종료되면 쉘은 **wait()**로부터 리턴하고 다시 프롬프트를 출력하고 다음 명령어를 기다립니다.  
  
**fork()**와 **exec()**을 분리함으로써 쉘은 많은 유용한 일을 조금 쉽게 할 수 있습니다.  
  
다음 예를 생각해봅시다.  
  
```prompt> wc p3.c > newfile.txt```
  
위의 예제에서 **wc** 프로그램의 출력은 **newfile.txt**라는 출력 파일로 **>** 표시를 통해 방향이 재지정됩니다.  
  
이러한 작업을 수행하는 방법은 간단합니다.  
  
자식이 생성되고 **exec()**이 호출되기 전에 **표준 출력(standard output)** 파일을 닫고 **newfile.txt** 파일을 엽니다.  
이런 작업을 해 놓으면 곧 실행될 프로그램인 wc의 출력은 모두 화면이 아니라 파일로 보내집니다.  
[아래 코드](#example-code---입출력-재지정의-모든-것p4c)에 작업을 수행하는 프로그램이 나와 있습니다.  

## Example Code - 입출력 재지정의 모든 것(p4.c)

```code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n ", (int) getpid());

  int rc = fork();

  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n ");
    exit(1);
  
  } else if (rc == 0) { // 자식: 표준 출력 파일로 재지정
    close(STDOUT_FILENO);
    open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    printf("hello, I am child (pid:%d)\n ", (int) getpid());
    char *myargs[3];
    myargs[0] = strdup("wc "); // 프로그램: "wc" (단어 세기)
    myargs[1] = strdup("p3.c "); // 인자: 단어를 셀 파일
    myargs[2] = NULL; // 배열의 끝 표시
    execvp(myargs[0], myargs); // "wc" 실행
    printf("this shouldn't print out ");
  
  } else { /// 부모 프로세스는 main의 경로를 따라 실행됩니다.
    int wc = wait(NULL);
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n ",
    rc, wc, (int) getpid());
  }

  return 0;
}
```

Unix 시스템은 미사용 중인 파일 디스크립터를 0번부터 찾아 나갑니다.  
이 경우, **STDOUT_FILENO**가 첫 번째 사용 가능 파일 디스크립터로 탐색되어, **open()**이 호출될 때 할당됩니다.  
이러한 이유는 표준 출력 파일을 닫았기 때문입니다.  
이후 자식 프로세스가 표준 출력 파일 디스크립터를 대상으로 하는 모든 쓰기,  
예를 들어 **printf()**에 의한 쓰기는 화면이 아니라 새로 열린 파일로 향하게 됩니다.

예제파일 [p4.c의 실행 결과](#입출력-재지정의-모든-것-result)는 다음과 같습니다.

### 입출력 재지정의 모든 것 Result

* **Process**
  hello world (pid:66314)  
   hello, I am parent of 66319 (wc:66319) (pid:66314)  
  
* **(p4.output, Filesystem)**
  hello, I am child (pid:66319)  
   this shouldn't print out  
  
이 출력 결과에는 두 가지의 흥미로운 점이 있습니다.  
  
첫째, **p4**를 실행하면, 화면에 아무 일도 일어나지 않는 것 처럼 보이나 실제로는 다음과 같은 일이 발생하였습니다.  
프로그램 **p4**는 **fork()**를 호출하여 새로운 자식 프로세스를 생성하고 **execvp()**를 호출하여 **wc** 프로그램을 실행시킵니다.  
출력이 **p4.output** 파일로 재지정되었기 때문에 화면에는 아무것도 출력되지 않습니다.  
출력 파일을 **cat**해 보면 **wc**를 실행시켰을 때 얻을 수 있는 모든 출력이 파일에 저장되어 있는 것을 발견하게 될 것입니다.  
Unix 파이프가 이와 유사한 방식으로 구현되지만 **pipe()** System Call을 통하여 생성됩니다.  
이 경우, 한 프로세스의 출력과 다른 프로세스의 입력이 동일한 파이프에 연결됩니다.  
한 프로세스의 출력은 자연스럽게 다음 프로세스의 입력으로 사용되고, 명령어 체인이 형성됩니다.  
파일에서 특정 단어가 몇 번 나오는지 세는 명령어 조합은 **grep**과 **wc**를 사용하면 쉽게 할 수 있습니다.  
**grep foo file | wc -l**을 명령어 프롬프트에 입력하고 결과에 놀라기만 하면 됩니다.  
프로세스 API를 간략하게 설명하였지만, 아직 실제로 배우고 이해해야 할 것들이 많이 남아습니다.  
예를 들면, 파일 디스크립터에 관해서는 파일 시스템에서 추후 이야기할 때 다루게 될 것입니다.  
지금 당장은 **fork() / exec()** 조합이 프로세스를 생성하고 조작하는 강력한 방법이라는 정도만 이해하면 충분합니다.  

### [출처 - 1](https://pages.cs.wisc.edu/~remzi/OSTEP/Korean/04-cpu-intro.pdf)

### [출처 - 2](https://pages.cs.wisc.edu/~remzi/OSTEP/Korean/05-cpu-api.pdf)
