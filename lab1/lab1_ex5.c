#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define PRINTF(obj) printf("Size of %s: %d\n", #obj, (int)sizeof(obj))

int main()
{
    PRINTF(char);
    PRINTF(short);
    PRINTF(short int);
    PRINTF(int);
    PRINTF(long int);
    PRINTF(unsigned int);
    PRINTF(void *);
    PRINTF(size_t);
    PRINTF(float);
    PRINTF(double);
    PRINTF(int8_t);
    PRINTF(int16_t);
    PRINTF(int32_t);
    PRINTF(int64_t);
    PRINTF(time_t);
    PRINTF(clock_t);
    PRINTF(struct tm);
    PRINTF(NULL);

    return 0;
}