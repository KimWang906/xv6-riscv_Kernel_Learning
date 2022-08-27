#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void
pwd(void) {
  // pwd 명령어를 구현하기 위해 알아야 할 순서 :

  // 함수 포인터
  /*
    현재 작업 디렉토리의 full path명을 null-terminated 문자열로 얻습니다.
    현재 작업 디렉토리를 저장할 buf의 크기(size)가 작으면  NULL을 return하며, errno에 ERANGE가 설정됩니다.
    만약 buf를 NULL로 설정하면 malloc(3)을 통해서 할당된 메모리에 작업디렉토리를 저장하여 return합니다.
    따라서 free(3)를 호출하여 메모리 해제를 해줘야 합니다.
  */

  // 현재 디렉터리가 메모리 어딘가에 있어야 커널이 사용할 수 있습니다.
  // --> 커널은 현재 디렉터리를 알고 있습니다.
  // 그러니 그게 어디에 저장되어 있는지 파악을 한 후,
  // 커널은 알고 있지만 유저가 그것을 가져올 방법은 없다는 것을 알 수 있습니다.
  // 따라서 현재 디렉터리를 가져오는 시스템 콜을 추가하고
  // pwd함수에서 해당 시스템 콜을 호출하면 됩니다.
  // 전통적으로 현재 디렉토리를 가져오는 시스템 콜은 getcwd 라는 이름입니다
  // 시스템 콜을 살펴보면 현재 디렉토리를 get 하는 시스템 콜은 없지만
  // set 하는 시스템 콜은 있으므로 해당 시스템 콜을 보면 어디에 저장되어 있는지 파악할 수 있습니다.

}

int main(int argc, char **argv) {
  pwd();
  exit(0);
}
