# Reference Counting

## 정의

참조 횟수 계산 방식(reference counting)은 메모리를 제어하는 방법 중 하나로, 쓰레기 수집의 한 방식이고 구성 방식이 매우 단순합니다.

어떤 한 동적 단위(객체, Object)가 참조값을 가지고 이 단위 객체가 참조(참조 복사)되면 참조값을 늘리고 참조한 다음 더이상 사용하지 않게 되면 참조값을 줄이면 됩니다.
참조값이 0이 되면 더이상 유효한 단위 객체로 보지 않아 메모리에서 제거합니다.

이 방식은 단위 객체에 대한 유/무효 처리가 사용하는 자리에서 확실하게 정해지며 참조값을 늘리고 줄이는 방법을 사용하기 때문에 빠릅니다.
또한 동적 쓰레기 수집을 하지 않는 프로그래밍 언어에서도 간단하게 구현할 수 있습니다.

## 단점

매번 참조할 때마다 참조값을 검사해야 하므로 많은 수의 단위 객체를 사용하게 되면 그 검사에 대한 부하가 커집니다.
또한 참조하는 단위 객체 사이에 서로 참조하게 되면 순환 참조 오류로 인해 잘못된 참조 파괴가 생기거나  
또는 단위 객체가 부모 없는 객체(orphaned)가 될 수 있습니다.

## Source Code

```code
struct object // 구조체 object를 생성
{
    int ref;
};

struct object* object_new(void)
{
    struct object* p = malloc(sizeof(struct object));
    p-> ref = 1;
    return p;
}

int object_ref(struct object* p)
{
    return (p-> ref++);
}

int object_unref(struct object* p)
{
    if ((p-> ref--) != 0)
        return p-> ref;
    else
    {
        free(p);
        return 0;
    }
}
```

## File System

참조 횟수 계산 방식은 여러 File System에서도 사용됩니다.  
File System에서는 파일 또는 할당된 디스크 블록에 참조 횟수를 저장하고,  
참조 횟수가 0이 되면 안전하게 블록을 해제할 수 있습니다.  
일부 유닉스 계열 운영체제에서는 디렉토리뿐만 아니라  
실행 중인 프로세스 또한 파일에 대한 참조 횟수를 가질 수 있습니다.  
만약 File System에서 파일이 삭제되었더라도,  
프로세스가 해당 파일을 열고 있다면 참조 횟수가 0이 아니므로 파일이 해제되지 않으며,  
해당 파일을 열고 있는 모든 프로세스가 파일을 닫으면 디스크에서 해제됩니다.
