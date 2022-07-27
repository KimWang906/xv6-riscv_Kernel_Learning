# 1-Intro

## 1. What is an OS?

<p align="center"><img src="/readme_img/1-intro-whatisanOS?.png"></p>

하드웨어(CPU, Memory, Input/Output) 위에서 곧바로 동작하면서 Application들을 위한 System call을 노출하면 뭐든지 OS다.

OS는 하드웨어를 여러 Application들이 공유할 수 있도록 나눠주는 역할도 하고, Application들이 하드웨어에 직접 접근하지 못하게 막는 역할도 한다.

### OS가 필요한 이유

1. 새로운 하드웨어를 만들어서 동작하게 만들기 위해서 필요합니다.
2. OS를 더 낫게(기능 개선, 성능 개선, 신뢰성, 에너지 효율성 등) 만들고 싶으면 OS를 배워야합니다.
3. 당장 스마트폰을 만들어서 유저들에게 가져다 팔려고 하기만 해도, 스마트폰에 있는 엑시노스같은 다양한 칩들을 다루는 OS가 필요합니다.
4. OS-aware 하드웨어를 설계할때에도 OS를 배워야해요.
5. 우리가 개발한 소프트웨어가 정확히 어떤 과정을 통해서 여러분의 모니터에 출력되는지 정확하게 알기 위해서도 OS를 배워야해요.
6. Linux Torvalds, "Just For Fun", 재미로 배울수도 있어요

## Application 관점에서 본 OS

Application이 돌아갈 수 있는 환경을 제공해줘요.
그리고 CPU나 메모리와 같은 하드웨어들에 대한 abstract view를 제공해줘요.

<ul>
    <li>Processors → 프로세서와 스레드로 추상화</li>
    <li>Memory → Address space (virtual memory)로 추상화</li>
    <li>Storage → Volumes, Directories, Files로 초상화</li>
    <li>I/O Devices → Files (+ioctls)</li>
    <li>Networks → Files (sockets, pipes, ...)</li>
</ul>
