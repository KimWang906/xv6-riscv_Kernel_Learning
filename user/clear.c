#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// 출력 전, 명령어들을 전부 저장하고 
void
clear(void) {
  printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A);
}


// argc = arguments count로 main 함수에 전달된 인자의 개수를 의미하며, 
// argv = arguments vector로서 가변적인 개수의 문자열이다.

int
main(int argc, char *argv[])
{
    clear();
    exit(0);
}
