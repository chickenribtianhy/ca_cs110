CC = gcc
CFLAGS = -g -std=c89 -Wpedantic -Wall -Wextra -Werror
TRANSLATOR_FILES = src/compression.c src/utils.c

ifeq ($(UNAME_S), Darwin)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes --dsymutil=yes --suppressions=osx_vector.supp
endif

all: translator

translator: clean
	$(CC) $(CFLAGS) -o translator translator.c $(TRANSLATOR_FILES)

clean:
	@-$(MAKE) --no-print-directory -C test clean
	@-rm -f *.o translator
	@-rm -rf __pycache__
	
grade: translator
	@$(MAKE) --no-print-directory -C test grade
