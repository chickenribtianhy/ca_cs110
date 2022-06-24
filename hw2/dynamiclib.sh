#!/bin/bash
gcc -o libringbuffer.so -fPIC -shared -Wpedantic -Wall -Wextra -Werror -std=c89 -c ringbuffer.c 
gcc -o test.o -c test.c -Wpedantic -Wall -Wextra -Werror -std=c89 
gcc -o dynamicringbuffer test.o -lc -L . -l:libringbuffer.so