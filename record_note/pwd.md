# PWD 명령어 만들어가며 쓰는 일지

## Linux man7 page

man7 페이지를 보는 법

    The standard sections of the manual include:

    1. User Commands
    2. System Calls
    3. C Library Functions
    4. Devices and Special Files
    5. File Formats and Conventions
    6. Games et. al.
    7. Miscellanea
    8. System Administration tools and Daemons

## Request

[getcwd(2)](https://github.com/torvalds/linux/blob/dcf8e5633e2e69ad60b730ab5905608b756a032f/fs/d_path.c#L412)  
  
이게 진짜 시스템콜이고  
  
* 현재 디렉토리 위치 리턴해주는 함수이고  코드를 보시면 아실 수 있으시겠지만 여기엔 buf가 NULL이라고 자동으로 동적할당하는 기능이 아예 하지 않습니다.
* 디렉토리 이름이 너무 길경우 에러 ENAMETOOLONG 를 반환하면서 실패합니다.
* 이 외에도 여러모로 유저가 직접 호출하기엔 불편한 인터페이스의 시스템 콜입니다.
  
[getcwd(3)](https://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/sysv/linux/getcwd.c)  
  
* getcwd_generic 라는 이름으로 정의한다음 #define getcwd getcwd_generic 이런걸 해서 유저가 자동으로 getcwd함수를 부르면 __getcwd_generic 함수가 대신 호출되도록 조작해놨습니다.
* 얘가 내부적으로 진짜 getcwd(2)를 호출합니다.
* buf가 NULL이면 커널에 넘기기 전에 자동으로 유저레벨에서 malloc(3)을 호출해서, 버퍼를 만든다음 getcwd(2) 에 넘겨주기 때문에 유저가 쓰기엔 좀 더 편합니다.
* 디렉토리 이름이 너무 길어서 getcwd(2)가 실패하면, 현재 디렉토리의 부모 디렉토리 이름을 하나하나 fstat lstat으로 얻어온 다음 그 부모 디렉토리 이름을 모두 연결하면서 리턴함 (;;) 느리긴 하겠지만 아무튼 이러면 유저는 에러 없이 편하게 현재 디렉토리의 위치를 무조건 받아올 수 있습니다.

**도움을 주신 xv6 스터디 방에 있는 모든 분들께 감사합니다.**

## 목표

1. **getcwd(2)** 구현하기  
2. **malloc(3), free(3)** 구현하기  
3. **getcwd(3)** 구현하기  

## Directory를 지정해주는 sys_chdir()

```c
uint64
sys_chdir(void) // 디렉터리를 변경하는 함수
{
  // MAXPATH  128 --> maximum file path name
  //                  최대 이름의 길이
  char path[MAXPATH]; // maximum file path name
  struct inode *ip;
  struct proc *p = myproc(); // 구조체 포인터에 할당되어 있는 myproc() 함수(proc.c)
  // 395번째 코드가 무엇을 뜻하는지 확실하게 알아서 올 것(질문)

  begin_op(); // called at the start of each FS system call(log.c)
  // 각 FS System Call이 시작될 때 호출됩니다.

  // argstr(int n, char *buf, int max) :

  // Fetch the nth word-sized system call argument as a null-terminated string.
  // Copies into buf, at most max.
  // Returns string length if OK (including nul), -1 if error.
  // 
  // n번째 워드 크기의 System Call 인수를 null로 종료된 문자열로 가져옵니다.
  // 최대 크기로 buf에 복사됩니다.
  // 정상이면 문자열 길이를 반환하고(null 포함), 오류이면 -1을 반환합니다.
  //

  // The fundamental job of “namei” algorithm is to convert a given path name to the corresponding inode number.
  // namei 알고리즘의 기본 작업은 주어진 경로 이름을 대응하는 inode 번호로 변환하는 것입니다.

  if(argstr(0, path, MAXPATH) < 0 || (ip = namei(path)) == 0){ // 이름이 최대 길이를 초과할 경우
    // called at the end of each FS system call.
    // commits if this was the last outstanding operation.
    // 각 FS System Call이 끝날 때 호출됩니다.
    // 이 작업이 마지막 처리되지 않은 작업인지 여부를 commit합니다.
    end_op();
    return -1; // return error
  }
  // ilock(struct inode*)
  // File System Code는 처음 inode를 잠근 경우에만 inode와 그 내용을 검사하고 수정할 수 있습니다.
  ilock(ip);
  if(ip->type != T_DIR) { // type이 Directory가 아닐 경우
    // 잠금 해제 후, 넣습니다.
    iunlockput(ip);
    end_op();
    return -1;
  }
  iunlock(ip);
  // iput(struct inode*)
  // Drop a reference to an in-memory inode.
  // If that was the last reference, the inode table entry can be recycled.
  // If that was the last reference and the inode has no links to it, free the inode (and its content) on disk.
  // All calls to iput() must be inside a transaction in case it has to free the inode.
  // 메모리 내에 있는 아이노드에 대한 참조를 삭제합니다.
  // 그것이 마지막 참조였다면, 아이노드 테이블 항목은 다시 사용될 수 있습니다.
  // 그것이 마지막 참조이고 아이노드에 링크가 없는 경우 디스크에서 아이노드와 그 내용을 해제합니다.
  // iput()에 대한 모든 호출은 아이노드를 free(해제)해야 하는 경우 트랜잭션 내에 있어야 합니다.
  iput(p->cwd);
  end_op();
  p->cwd = ip; // 변경된 디렉터리의 상태를 반영합니다.

  return 0;
}
```

코드 분석을 통해 chdir()의 정확한 로직을 알게 되었고 inode의 개념과 자료구조 Reference Counting에 대해 알게 되었습니다.

## [유저에게 Directory를 알려주는 sys_getcwd() 함수 만들기](https://man7.org/linux/man-pages/man3/getcwd.3.html)

<!-- // getcwd(char* buf, size)  
// return: 호출이 성공하면 buf의 포인터를 반환하고, 실패할 경우 NULL을 반환합니다.   -->

```c
// 내일은 Linux getcwd() 관련 함수를 분석할 예정.
SYSCALL_DEFINE2(getcwd, char __user *, buf, unsigned long, size)
{
    int error;
    struct path pwd, root;
    char *page = __getname();

    if (!page)
    return -ENOMEM;

// RCU : Read Copy Update
// RCU 구현시 필요한 자료구조(리스트)를 초기화 해줍니다.

/*
RCU(Read Copy Update)는 읽는 작업이 주로 이루어지는 자료구조를 보호하기 위한 또 하나의 동기화 기법입니다.
다른 동기화 방법과는 다르게 락이나 카운터를 사용하지 않습니다.
이것은 캐시 라인의 스누핑이나 무효 값으로 인해 과부하를 발생시키는 "읽기/쓰기 스핀 락"이나 seqlocks에 비해 굉장히 유리합니다.

rcu_read_lock()
RCU에서 데이터를 참조하기 위한 Critical Section을 시작 했다는 것을 알립니다.
preempt_disable() - CPU간의 선점을 방지합니다.
__acquire(RCU) - 읽기을 위한 잠금 권한을 획득합니다. 
읽는 것은 다수의 스레드에서 접근이 가능하므로 다른 CPU에서 rcu_read_lock() 함수를 이용하여 중첩해서 사용이 가능합니다.

rcu_read_unlock()
RCU에서 데이터의 참조가 끝난것을 통지합니다.
__release(RCU) - __acquire()에서 획득한 잠금을 해제합니다.
*/
    rcu_read_lock(); 
    get_fs_root_and_pwd_rcu(current->fs, &root, &pwd);

    if (unlikely(d_unlinked(pwd.dentry))) {
        rcu_read_unlock();
        error = -ENOENT;
    } else {
        unsigned len;
        DECLARE_BUFFER(b, page, PATH_MAX);

        prepend_char(&b, 0);
        if (unlikely(prepend_path(&pwd, &root, &b) > 0))
            prepend(&b, "(unreachable)", 13);
        rcu_read_unlock();

        len = PATH_MAX - b.len;
        if (unlikely(len > PATH_MAX))
        // 디렉토리 이름이 너무 길경우 에러 'ENAMETOOLONG' 를 반환하면서 실패합니다
            error = -ENAMETOOLONG;
        else if (unlikely(len > size))
            error = -ERANGE;
        else if (copy_to_user(buf, b.buf, len))
            error = -EFAULT;
        else
            error = len;
    }
    __putname(page);

    return error;
}
```

### 참고 자료

[디렉터리 다루기](https://velog.io/@jyong0719/%EB%94%94%EB%A0%89%ED%86%A0%EB%A6%AC-%EB%8B%A4%EB%A3%A8%EA%B8%B0)

[man7 - getcwd(3)](https://man7.org/linux/man-pages/man3/getcwd.3.html)

[운영체제](https://chul2-ing.tistory.com/39)

[포인터 함수, 함수 포인터의 차이점](https://visualguide.org/ko/c-%ED%8F%AC%EC%9D%B8%ED%84%B0%EC%97%90-%EB%8C%80%ED%95%9C-%ED%8F%AC%EC%9D%B8%ED%84%B0-%ED%95%A8%EC%88%98%EC%97%90-%EB%8C%80%ED%95%9C-%ED%8F%AC%EC%9D%B8%ED%84%B0-%EC%98%88%EC%A0%9C%EC%99%80-%ED%95%A8)

[참조 횟수 계산 방식](https://ko.wikipedia.org/wiki/%EC%B0%B8%EC%A1%B0_%ED%9A%9F%EC%88%98_%EA%B3%84%EC%82%B0_%EB%B0%A9%EC%8B%9D)

[OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/Korean/)

[getcwd()](https://www.it-note.kr/209)

[namei() function](https://www.quora.com/Linux-Kernel-How-do-the-path-look-up-mechanism-namei-work-in-Linux)

## 저에게 도움을 주신 모든 분들께 항상 감사합니다
