# 1-Intro

## 1. What is an OS?

<p align="center"><img src="/readme_img/1-intro-whatisanOS?.png"></p>

하드웨어(CPU, Memory, Input/Output) 위에서 곧바로 동작하면서 Application들을 위한 System call을 노출하면 뭐든지 OS입니다.

OS는 하드웨어를 여러 Application들이 공유할 수 있도록 나눠주는 역할도 하고, Application들이 하드웨어에 직접 접근하지 못하게 막는 역할도 합니다.

### OS가 필요한 이유

1. 새로운 하드웨어를 만들어서 동작하게 만들기 위해서 필요합니다.
2. OS를 더 낫게(기능 개선, 성능 개선, 신뢰성, 에너지 효율성 등) 만들고 싶으면 OS를 배워야합니다.
3. 당장 스마트폰을 만들어서 유저들에게 가져다 팔려고 하기만 해도, 스마트폰에 있는 엑시노스같은 다양한 칩들을 다루는 OS가 필요합니다.
4. OS-aware 하드웨어를 설계할때에도 OS를 배워야합니다.
5. 우리가 개발한 소프트웨어가 정확히 어떤 과정을 통해서 여러분의 모니터에 출력되는지 정확하게 알기 위해서도 OS를 배워야합니다.
6. Linux Torvalds, "Just For Fun", 재미로 배울 수 있습니다.

## Application 관점에서 본 OS

Application이 돌아갈 수 있는 환경을 제공합니다.
그리고 CPU나 메모리와 같은 하드웨어들에 대한 abstract view를 제공합니다.

<ul>
    <li>Processors → 프로세서와 스레드로 추상화</li>
    <li>Memory → Address space (virtual memory)로 추상화</li>
    <li>Storage → Volumes, Directories, Files로 초상화</li>
    <li>I/O Devices → Files (+ioctls)</li>
    <li>Networks → Files (sockets, pipes, ...)</li>
</ul>

## System 관점에서 본 OS

CPU, RAM, IO 장치 등의 자원들을 여러 Application이 쓸 수 있게 나눠줍니다.

### Sharing

<ul>
    <li>Time multiplexing: 시분할 공유. CPU 스케줄링, 등</li>
    <li>Space multiplexing: 공간분할 공유. 버추얼메모리, 하이퍼스레딩, 등</li>
</ul>

### Sharing할 때 중요한 것들

<ul>
    <li>Protection: 다른 프로세스의 메모리를 볼 수 있으면 안되고, 주어진 것보다 더 많은 메모리를 쓸 수 있으면 안됩니다, etc</li>
    <li>Fairness: Starvation이 일어나면 안됩니다, etc</li>
    <li>Efficiency</li>
</ul>

## OS의 역사

### 1세대

<ul>
    <li>1세대 컴퓨터(1945 ~ 1955)는 <b>진공관</b>과 <b>Plugboard</b>로 프로그래밍을 하였습니다.</li>
    <li>1세대에는 <b>OS</b>, <b>PL</b>, <b>어셈블리어</b>가 존재하지 않았습니다.</li>
</ul>

### 2세대

2세대 컴퓨터(1955 ~ 1965)는 트랜지스터와 메인프레임으로 프로그래밍하였습니다.
<ul>
    <li>Batch System: One job at a time</li>
    <li>천공카드, Tape drives, Line printers를 사용했습니다.</li>
    <li>OS는 메모리에 항상 상주하며, OS를 사용할 일이 거의 없었기 때문에 실행되는 일이 적었습니다.</li>
    <li>CPU는 I/O 병목현상으로 인해 적게 사용되었습니다.</li>
</ul>

### 3세대

3세대 컴퓨터(1965 ~ 1980)는 Integrated circuit(집적회로)가 만들어져서 컴퓨터가 저렴해지고 빨라졌으며, 디스크 드라이브도 발전하였습니다.
On-line terminals이라는 것도 생겼습니다.

하드웨어 호환을 유지하기위해 "Computer Architecture"라는 개념이 처음 나왔습니다.
이 ISA(Instruction Set Architecture) 스펙이 정의된 최초의 컴퓨터가 IBM System / 360 Family 였습니다.

3세대에 Multiprogramming systems이 등장했습니다.
IBM OS/360 (1964), 여러사람이 job(작업)을 submit하고 이 job(작업)들이 아주아주 긴 Queue(대기열)에 등록되어있었습니다.

<b>다음은 3세대 Multiprogramming systems의 기능입니다.

<ul>
    <li>Job scheduling</li>
    <li>메모리 관리</li>
    <li>CPU 스케줄링</li>
    <li>컨커런시</li>
    <li>Protection</li>
    <li>Spooling(Simultaneous Peripheral Operation On-Line)</li>
    : 출력하는동안 프린터기에 block 되지 않고 컴퓨터를 계속 사용할 수 있습니다.
</ul></b>

3세대에는 Time-sharing systems도 등장했습니다.
해당 System은 응답시간이 훨씬 좋아졌고 사용된 운영체제는 MIT CTSS(1961), Multics(1965), Unix(1969) 등이 있습니다.

현재 우리가 쓰고있는 OS의 거의 대부분의 기능은 이 시점에 개발되었습니다.

<b>다음은 3세대 Time-sharing systems의 기능입니다.

<ul>
    <li>복잡하고 미세한 CPU 스케줄링</li>
    <li>가상메모리, 스와핑</li>
    <li>파일시스템</li>
    <li>동기화</li>
    <li>IPC (프로세스간 통신)</li>
    <li>Interactive shell</li>
    <li>더 많은 보호, etc</li>
</ul></b>

### 4세대

