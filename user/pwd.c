/*
#include <sys/types.h>
#include <sys/stat.h>
#include <xv6/fs.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
inum(char *path)
{
  struct stat st;
  int fd;

  fd = open(path, O_RDONLY);
  if(fstat(fd, &st) < 0){
    fprintf(stderr, "pwd: cannot stat %s\n", path);
    exit(1);
  }
  close(fd);
  return st.ino;
}

void
dirent_by_inum(char *dir_path, int inum, struct dirent *res)
{
  struct dirent de;
  int dir;

  dir = open(dir_path, O_RDONLY);
  while(read(dir, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == inum){
      break;
    }
  }
  close(dir);
  *res = de;
}

void
strprepend(char *dest, char *src, int n)
{
  memmove(dest + strlen(src), dest, n - strlen(src));
  memmove(dest, src, strlen(src));
}

int
main(int argc, char *argv[])
{
  char cur[256] = ".", parent[256] = "..";
  char res[256] = "";

  while(inum(cur) != inum(parent)){
    struct dirent cur_dirent;
    dirent_by_inum(parent, inum(cur), &cur_dirent);
    strprepend(res, cur_dirent.name, sizeof(res));
    strprepend(res, "/", sizeof(res));

    strcpy(cur, parent);
    strprepend(parent, "../", sizeof(parent));
  }
  if(res[0] == '\0'){
    strprepend(res, "/", sizeof(res));
  }
  printf("%s\n", res);

  exit(0);
}

참고하는 코드 
*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

// namei() 함수 조사 필요.
// namei() 함수는 

void
pwd(void) {
  // pwd() 함수가 작동하는 로직 :
  // 디렉터리의 경로를 구한다( /(root)에서부터 나의 현재 디렉터리까지 반복문을 돌린다.)
  // ex 나의 경로가 /home/test라면
  // /(root) home(Subdirectories) / test(Subdirectories)
  // root에서부터       -------------->     MyDirectory까지
  // 참고해야 하는 파일(user/ls.c ; kernel/fs.h)
  // ls.c(ls 명령어)는 현재 디렉터리에 있는 하위 디렉터리를 리스트로 출력한다.
  // fs.h(filesystem 헤더파일)
}

int main(int argc, char **argv) {
  pwd();
  exit(0);
}
