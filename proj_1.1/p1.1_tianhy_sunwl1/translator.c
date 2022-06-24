/*  Project 1.1: RISC-V instructions to RISC-V compressed instructions in C89.
    The following is the starter code provided for you. To finish the task, you 
    should define and implement your own functions in translator.c, compression.c, 
    utils.c and their header files.
    Please read the problem description before you start.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "src/compression.h"
#include "src/utils.h"

#include "translator.h"

/*check if file can be correctly opened */
static int open_files(FILE **input, FILE **output, const char *input_name, const char *output_name)
{
    *input = fopen(input_name, "r");
    if (!*input)
    { /* open input file failed */
        printf("Error: unable to open input file: %s\n", input_name);
        return -1;
    }

    *output = fopen(output_name, "w");
    if (!*output)
    { /* open output file failed */
        printf("Error: unable to open output file: %s\n", output_name);
        fclose(*input);
        return -1;
    }
    return 0; /* no problem opening files */
}

static int close_files(FILE **input, FILE **output)
{
    fclose(*input);
    fclose(*output); /* close the files at the end */
    return 0;
}

static void print_usage_and_exit()
{
    printf("Usage:\n");
    printf("Run program with translator <input file> <output file>\n"); /* print the correct usage of the program */
    exit(0);
}

/*Run the translator 
*/
int translate(const char *in, const char *out)
{
    FILE *input, *output;
    int err = 0;
    /* char instr[33]; */
    char c_instr[20];    /* compressed form */
    char instrs[60][40]; /* instr */
    int is_comp[60];     /* whether an instr is compressible */
    int counter;         /* counter of lines of instrs */
    int i;
    int temp; /* temporary id */
    if (in)
    { /* correct input file name */
        if (open_files(&input, &output, in, out) != 0)
            exit(1);

        counter = 0;
        /* read and write */
        memset(is_comp, 0, sizeof(is_comp));
        while (fgets(instrs[counter], 36, input))
        {
            /* see whether each instruction is compressible or not, 
            for jump and branch */
            instrs[counter][32] = '\0';                          /* be careful with string */
            is_comp[counter] = is_compressible(instrs[counter]); /* see whether compressible */
            /* is_comp[counter] = compress_instr(instrs[counter], c_instr, is_comp, counter); */
            ++counter;
        }
        for (i = 0; i < counter; ++i)
        {
            temp = compress_instr(instrs[i], c_instr, is_comp, i); /* compress it to c_instr if compressible */
            if (temp == 0)
            {
                /* write it into output */
                fprintf(output, "%s\n", instrs[i]);
            }
            else
            {
                /* translate the 32-bit string instr[] */
                fprintf(output, "%s\n", c_instr);
                memset(c_instr, 0, sizeof(c_instr)); /* careful with memory */
            }
        }

        close_files(&input, &output);
    }
    return err;
}

/* main func */
int main(int argc, char **argv)
{
    char *input_fname, *output_fname;
    int err;

    if (argc != 3) /* need correct arguments */
        print_usage_and_exit();

    input_fname = argv[1];
    output_fname = argv[2];

    err = translate(input_fname, output_fname); /* main translation process */
    if (err)
        printf("One or more errors encountered during translation operation.\n"); /* something wrong */
    else
        printf("Translation process completed successfully.\n"); /* correctly output */

    return 0;
}