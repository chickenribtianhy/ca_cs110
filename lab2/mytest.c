#include <stdio.h>

int main()
{

    unsigned x = 1;
    unsigned y = 0b1100;
    y=y>>1;
    printf("%d\n", x & y);
    return 0;
}