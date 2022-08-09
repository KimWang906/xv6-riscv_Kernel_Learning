# Code

* **defs.h** • Function 정의용
* **proc.h**, **proc.c** • Process 관련 기능용
* **console.c** • Console 입력 처리용
* **syscall.c**, **sysprosc.c** • System Call 구현용

## Day 1 homeworks

### 함수 정의

#### setpgid

    int setpgid(int pid, int pgid);

* **setpgid**는 **pid**로 지정된 Process의 Process Group ID를 **pgid**로 변경해야 합니다.
* **pid** 및 **pgid**는 음이 아닌 정수입니다.
* **pid**가 0이면 Call의 Process Group ID를 변경해야 합니다.
  * Process(System Call을 호출한 Process)
* **pgid**가 0이면 Process Group ID를 **pid**와 동일하게 변경해야 합니다.
* **setpgid**는 다음과 같은 값을 **return** 합니다.
  * 변경에 성공할 시, 0을 **return**합니다.
  * 변경에 실패할 시, -1을 **return**합니다.

#### getpgid

    int getpgid(int pid);

* **getpgid**는 **pid**로 지정된 Process의 Process Group ID를 **return**해야 합니다.
* **pid**가 0이면 Return Process의 Process Group ID를 **return**해야 합니다.
* **getpgid**은 다음과 같은 값을 **return** 합니다.
  * 성공할 시, **pgid**를 **return**합니다.
  * 실패할 시, -1을 **return**합니다.

## OSTEP 정리 노트

### [Process](process.md)
