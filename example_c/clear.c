#include <stdio.h>

#define clear() printf("\033[H\033[J")

int main(void)
{
    printf("Hello world!\n");
    clear();
    return 0;
}
