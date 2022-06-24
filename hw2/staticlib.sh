#!/bin/bash
gcc -c ringbuffer.c -Wpedantic -Wall -Wextra -Werror -std=c89 -o ringbuffer.o
gcc -c test.c -Wpedantic -Wall -Wextra -Werror -std=c89 -o test.o
ar -rcs libringbuffer.a ringbuffer.o
ld -o staticringbuffer test.o -lc -L . -l:libringbuffer.a