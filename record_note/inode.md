# inode(아이노드)

**inode**는 이름이 지정되지 않은 단일 파일을 나타냅니다.

**inode** 디스크 구조에는 메타데이터가 포함되어 있습니다.
파일의 **type, size, 참조하는 링크 수 및 파일 내용**을 포함하는 **Block의** 목록입니다.
  
**inode**는 **sb.start** **inode**의 디스크에 순차적으로 배치되고,  
각 **inode**는 디스크 상의 위치를 나타내는 수를 가지고 있습니다.  
  
커널은 사용 중인 **inode**의 테이블을 메모리에 보관합니다.
접근을 동기화할 수 있는 장소를 제공합니다.
여러 프로세스에서 사용하는 **inode**로 이동합니다.
**in-memory** **inode**는 디스크에 저장되지 않은 **book-keeping** 정보(**ip->ref 및 ip->valid**)를 포함합니다.  
  
**inode**와 그 메모리 내 표현은 **File System Code**의 나머지 부분에서 사용될 수 있기 전에 일련의 상태를 거칩니다.  
  
* **Allocation**: (디스크에서) **Type**이 0이 아닌 경우 **inode**가 할당됩니다.  
**ialloc()** 는 할당하고, 참조 및 링크 수가 0으로 떨어지면 **iput()** 은 비워집니다.  
  
* **Referencing in table**: **ip->ref**가 0일 경우 **inode** 표의 항목은 무료입니다.  
  그렇지 않으면 **ip->ref**는 엔트리에 대한 메모리 내 포인터 수(열린 파일 및 현재 디렉터리)를 추적합니다.  
  **iget()** 은 테이블 항목을 찾거나 만들고 참조를 증가시키며, **iput()** 은 참조를 감소시킵니다.  
  
* **Valid**: **inode** 테이블 항목의 정보(**type, size, &c**)는 **ip->valid**가 1인 경우에만 정확합니다.  
  **ilock()** 은 **inode**를 읽습니다.  
 디스크가 **ip->valid**를 설정하고 **iput()** 는 **ip->ref**가 0으로 떨어지면 **ip->valid**를 지웁니다.  
  
* **Locked**: **File System Code**는 처음 **inode**를 잠근 경우에만 **inode**와 그 내용을 검사하고 수정할 수 있습니다.  
  
따라서 일반적인 코드는 다음과 같습니다.  

```code
 ip = iget(dev, inum)
 ilock(ip)
 ...ip->xxx...를 검사하고 수정합니다.
 i unlock(ip)
 iput(ip)
```

**ilock()** 는 **iget()** 와 분리되어 **System call**이 **inode**에 대한 장기적인 참조를 얻을 수 있고 짧은 시간 동안만 잠글 수 있습니다. (예: 읽기 파일)  
분리는 또한 경로 이름 조회 중 **deadlock** 및 **races**를 방지하는 데에 도움이 됩니다.  
**iget()** 은 **ip->ref**를 증가시켜 **inode**가 테이블에 남아 있고 포인터가 유효하게 유지되도록 합니다.  
  
많은 내부 **File System Function**는 호출자가 관련된 **inode**를 잠금하였다고 생각합니다.  
  
**itable.lock** **spinlock**은 테이블 항목의 할당을 보호합니다.  
**ip->ref**는 항목이 비어 있는지 여부를 나타내고 **ip->dev**와 **ip->inum**은 항목이 어떤 **i-node**를 보유하는지 나타내므로, 이러한 필드 중 하나를 사용하는 동안 **itable.lock**을 보유해야 합니다.  
  
**ip->lock lock**은 **ref, dev, inum**을 제외한 모든 **ip-> fields**를 보호합니다.  
**ip->lock**은 **inode**의 **ip->valid, ip->size, ip->type, &c**를 읽거나 쓰려면 **ip->lock**을 사용해야 합니다.  
