#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  Result Value

  hello world (pid:46316)
   hello, I am parent of 46320 (pid:46316)
   hello, I am child (pid:46320)
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

  } else { // 부모 프로세스는 main의 경로를 따라 실행됩니다.
    printf("hello, I am parent of %d (pid:%d)\n ",
    rc, (int) getpid());
  }

  return 0;
}
