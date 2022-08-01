# Spinlock

스핀락(spinlock)은 임계 구역(critical section)에 진입이 불가능할 때 진입이 가능할 때까지 루프를 돌면서 재시도하는 방식으로 구현된 락을 가리킵니다.</br>
스핀락이라는 이름은 락을 획득할 때까지 해당 스레드가 빙빙 돌고 있다(spinning)는 것을 의미합니다.</br>
스핀락은 queue의 한 종류입니다.</br>
</br>
스핀락은 운영 체제의 스케줄링 지원을 받지 않기 때문에, 해당 스레드에 대한 문맥 교환이 일어나지 않습니다.</br>
따라서 스핀락은 임계 구역에 짧은 시간 안에 진입할 수 있는 경우에 문맥 교환을 제거할 수 있어 효율적입니다.</br>
하지만 만약 스핀락이 오랜 시간을 소요한다면 다른 스레드를 실행하지 못하고 대기하게 되며, 이 경우 비효율적인 결과를 가져옵니다.</br>

다음은 **스핀락을 구현하기 위해 x86 어셈블리어를 사용한 예제이고, 인텔 80386 호환 프로세서일 경우 실제로 동작합니다.**

    ; Intel syntax

    locked:                      ; The lock variable. 1 = locked, 0 = unlocked.
        dd      0

    spin_lock:
        mov     eax, 1          ; Set the EAX register to 1.

        xchg    eax, [locked]   ; Atomically swap the EAX register with
                                ;  the lock variable.
                                ; This will always store 1 to the lock, leaving
                                ;  the previous value in the EAX register.

        test    eax, eax        ; Test EAX with itself. Among other things, this will
                                ;  set the processor's Zero Flag if EAX is 0.
                                ; If EAX is 0, then the lock was unlocked and
                                ;  we just locked it.
                                ; Otherwise, EAX is 1 and we didn't acquire the lock.

        jnz     spin_lock       ; Jump back to the MOV instruction if the Zero Flag is
                                ;  not set; the lock was previously locked, and so
                                ; we need to spin until it becomes unlocked.

        ret                     ; The lock has been acquired, return to the calling
                                ;  function.

    spin_unlock:
        mov     eax, 0          ; Set the EAX register to 0.

        xchg    eax, [locked]   ; Atomically swap the EAX register with
                                ;  the lock variable.

        ret                     ; The lock has been released.
