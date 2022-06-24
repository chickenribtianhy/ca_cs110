#!/bin/bash
gcc -c ringbuffer.c -Wpedantic -Wall -Wextra -Werror -std=c89 -o ringbuffer.o
gcc -c test.c -o test.o -Wpedantic -Wall -Wextra -Werror -std=c89
ar -rcs libringbuffer.a ringbuffer.o
ld test.o -o staticringbuffer -lc -L. -l:libringbuffer.a