# Clear 명령어

## 기능

화면을 정리하여 줍니다.
(추후 GUI 구현 후 clear 명령어 재작성 예정)

## 코드 설명

```code
#include "kernel/types.h" // type에 관한 헤더파일
#include "kernel/stat.h" // 파일의 크기나 종류를 구별할 수 있게하는 헤더파일
#include "user/user.h" // 유저 함수 정의 파일

// 출력 전, 명령어들을 전부 저장하고 
void
clear(void) {
    // 화면을 정리할 수 있게 콘솔에 신호를 주는 코드    
    printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A); 
}

// argc = arguments count로 main 함수에 전달된 인자의 개수를 의미하며, 
// argv = arguments vector로서 가변적인 개수의 문자열이다.

int
main(int argc, char *argv[])
{
    clear();
    exit(0); // 프로세스 종료
}
```
