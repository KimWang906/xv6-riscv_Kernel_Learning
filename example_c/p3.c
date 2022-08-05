#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
  Result Value

  hello world (pid:56900)
   hello, I am child (pid:56905)
   this shouldn't print out  hello, I am parent of 56905 (wc:56905) (pid:56900)
*/

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
