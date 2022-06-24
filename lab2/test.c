#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[] = "faq";
    // int a=10;
    // int *p=NULL;
    int *p=10;
    char *q = '1';
    printf("%p\n", p);
    // printf("%d\n", p[0]);
    printf("%p,\n%p\n\n", &p, p);
    printf("%p\n", &name);
    printf("%ld\n", sizeof(name));
    return 0;
}