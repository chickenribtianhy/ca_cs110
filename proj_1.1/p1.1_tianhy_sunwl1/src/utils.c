#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int add_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = '1'; /* one by one */
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[8 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '1';
    c_instr[15] = '0';  /* one by one */
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int mv_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0'; /* one by one */
    c_instr[3] = '0';
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '1'; /* one by one */
    c_instr[15] = '0';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int sub_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = '0'; /* one by one */
    c_instr[4] = '1';
    c_instr[5] = '1'; /* one by one */
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* func */
    c_instr[9] = '0'; /* one by one */
    c_instr[10] = '0';
    /* rs2 */
    for (i = 11; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int and_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1'; /* one by one */
    c_instr[1] = '0';
    c_instr[2] = '0'; /* one by one */
    c_instr[3] = '0';
    c_instr[4] = '1'; /* one by one */
    c_instr[5] = '1';
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* func */
    c_instr[9] = '1';
    c_instr[10] = '1'; /* one by one */
    /* rs2 */
    for (i = 11; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int or_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = '0'; /* one by one */
    c_instr[4] = '1';
    c_instr[5] = '1'; /* one by one */
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* func */
    c_instr[9] = '1';
    c_instr[10] = '0';
    /* rs2 */
    for (i = 11; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int xor_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1'; /* one by one */
    c_instr[1] = '0';
    c_instr[2] = '0'; /* one by one */
    c_instr[3] = '0';
    c_instr[4] = '1'; /* one by one */
    c_instr[5] = '1';
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* func */
    c_instr[9] = '0'; /* one by one */
    c_instr[10] = '1';
    /* rs2 */
    for (i = 11; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int jr_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1'; /* one by one */
    c_instr[1] = '0';
    c_instr[2] = '0'; /* one by one */
    c_instr[3] = '0';
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[8 + i]; /* rs1 */
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = '0';
    /* opcode */
    c_instr[14] = '1'; /* one by one */
    c_instr[15] = '0';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int jalr_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1'; /* one by one */
    c_instr[1] = '0';
    c_instr[2] = '0'; /* one by one */
    c_instr[3] = '1';
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[8 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = '0';
    /* opcode */
    c_instr[14] = '1'; /* one by one */
    c_instr[15] = '0';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int li_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '0'; /* one by one */
    c_instr[1] = '1';
    c_instr[2] = '0'; /* one by one */
    c_instr[3] = instr[0];
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int addi_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '0'; /* one by one */
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = instr[0];
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int slli_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '0';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = instr[6];
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '1'; /* one by one */
    c_instr[15] = '0';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int andi_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1'; /* one by one */
    c_instr[1] = '0';
    c_instr[2] = '0';
    c_instr[3] = instr[0]; /* one by one */
    c_instr[4] = '1';
    c_instr[5] = '0'; /* one by one */
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int srli_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = instr[6]; /* one by one */
    c_instr[4] = '0';
    c_instr[5] = '0'; /* one by one */
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '1';  /* one by one */
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int srai_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = instr[6]; /* one by one */
    c_instr[4] = '0';
    c_instr[5] = '1';
    /* rd */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int lw_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '0';
    c_instr[1] = '1'; /* one by one */
    c_instr[2] = '0';
    /* rd */
    for (i = 3; i < 6; ++i)
        c_instr[i] = instr[3 + i];
    /* rs2 */
    for (; i < 9; ++i)
        c_instr[i] = instr[i + 8];
    c_instr[9] = instr[9];
    c_instr[10] = instr[5]; /* one by one */
    for (i = 11; i < 14; ++i)
        c_instr[i] = instr[i + 11];
    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '0';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int lui_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '0';
    c_instr[1] = '1'; /* one by one */
    c_instr[2] = '1';
    c_instr[3] = instr[14];
    /* rd */
    for (i = 4; i < 9; ++i)
        c_instr[i] = instr[16 + i];
    /* rs2 */
    for (; i < 14; ++i)
        c_instr[i] = instr[i + 6];
    /* opcode */
    c_instr[14] = '0'; /* one by one */
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int sw_compress(char *instr, char *c_instr)
{
    int i;
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '1'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = instr[6];
    c_instr[4] = instr[20]; /* one by one */
    c_instr[5] = instr[21];
    /* rs2 */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[i + 8];
    c_instr[9] = instr[22]; /* one by one */
    c_instr[10] = instr[5];
    for (i = 11; i < 14; ++i)
        c_instr[i] = instr[i - 2];
    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '0';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int beq_compress(char *instr, char *c_instr)
{
    int i;

    /* func */
    c_instr[0] = '1';
    c_instr[1] = '1'; /* one by one */
    c_instr[2] = '0';
    c_instr[3] = instr[3];
    c_instr[4] = instr[20]; /* one by one */
    c_instr[5] = instr[21];
    /* rs2 */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[i + 8];
    c_instr[9] = instr[4];
    c_instr[10] = instr[5]; /* one by one */
    c_instr[11] = instr[22];
    c_instr[12] = instr[23]; /* one by one */
    c_instr[13] = instr[6];
    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int bne_compress(char *instr, char *c_instr)
{
    int i;

    /* func */
    c_instr[0] = '1';
    c_instr[1] = '1'; /* one by one */
    c_instr[2] = '1';
    c_instr[3] = instr[3]; /* one by one */
    c_instr[4] = instr[20];
    c_instr[5] = instr[21]; /* one by one */
    /* rs2 */
    for (i = 6; i < 9; ++i)
        c_instr[i] = instr[i + 8];
    c_instr[9] = instr[4];
    c_instr[10] = instr[5]; /* one by one */
    c_instr[11] = instr[22];
    c_instr[12] = instr[23];
    c_instr[13] = instr[6]; /* one by one */
    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int j_compress(char *instr, char *c_instr)
{
    int i;
    int runing; /* the running status */
    if (instr[0] == '0')
    {
        runing = 1; /* default */
        for (i = 10; i >= 1; --i)
        {
            if (instr[i] == '1')
            {
                instr[i] = '0'; /* subtraction */
                runing = 0;
                break;
            }
            else
                instr[i] = '1'; /* subtraction */
        }
        if (runing != 0)
        {
            if (instr[11] == '1') /* subtraction */
            {
                instr[11] = '0'; /* subtraction */
                runing = 0;
            }
            else
                instr[i] = '1'; /* subtraction */
        }
        if (runing != 0)
            for (i = 19; i >= 12; --i)
            {
                if (instr[i] == '1') /* subtraction */
                {
                    instr[i] = '0'; /* subtraction */
                    runing = 0;
                    break;
                }
                else
                    instr[i] = '1'; /* subtraction */
            }
    }
    /* func */
    c_instr[0] = '1';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '1';
    c_instr[3] = instr[11];  /* 11 */
    c_instr[4] = instr[7];   /* 4 */
    c_instr[5] = instr[2];   /* 9 */
    c_instr[6] = instr[3];   /* 8 */
    c_instr[7] = instr[1];   /* 10 */
    c_instr[8] = instr[5];   /* 6 */
    c_instr[9] = instr[4];   /* 7 */
    c_instr[10] = instr[8];  /* 3 */
    c_instr[11] = instr[9];  /* 2 */
    c_instr[12] = instr[10]; /* 1 */
    c_instr[13] = instr[6];  /* 5 */

    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

int jal_compress(char *instr, char *c_instr)
{
    int i;
    int runing; /* the running status */
    if (instr[0] == '0')
    {
        runing = 1; /* default */
        for (i = 10; i >= 1; --i)
        {
            if (instr[i] == '1') /* subtraction */
            {
                instr[i] = '0'; /* subtraction */
                runing = 0;
                break;
            }
            else
                instr[i] = '1'; /* subtraction */
        }
        if (runing != 0)
        {
            if (instr[11] == '1') /* subtraction */
            {
                instr[11] = '0'; /* subtraction */
                runing = 0;
            }
            else
                instr[i] = '1'; /* subtraction */
        }
        if (runing != 0)
            for (i = 19; i >= 12; --i)
            {
                if (instr[i] == '1') /* subtraction */
                {
                    instr[i] = '0'; /* subtraction */
                    runing = 0;
                    break;
                }
                else
                    instr[i] = '1'; /* subtraction */
            }
    }
    /* func */
    c_instr[0] = '0';
    c_instr[1] = '0'; /* one by one */
    c_instr[2] = '1';
    c_instr[3] = instr[11];  /* 11 */
    c_instr[4] = instr[7];   /* 4 */
    c_instr[5] = instr[2];   /* 9 */
    c_instr[6] = instr[3];   /* 8 */
    c_instr[7] = instr[1];   /* 10 */
    c_instr[8] = instr[5];   /* 6 */
    c_instr[9] = instr[4];   /* 7 */
    c_instr[10] = instr[8];  /* 3 */
    c_instr[11] = instr[9];  /* 2 */
    c_instr[12] = instr[10]; /* 1 */
    c_instr[13] = instr[6];  /* 5 */

    /* opcode */
    c_instr[14] = '0';
    c_instr[15] = '1';
    c_instr[16] = '\0'; /* careful with string */
    return 1;
}

/* return 2's power */
int pow1(int x, int y)
{
    int i;
    int s; /* product */
    s = 1; /* default */
    for (i = 0; i < y; ++i)
        s *= x; /* multiply */
    return s;
}

void deci2bin_2(int imm, char *instr)
{
    int i;
    /* imm1:10 */
    for (i = 10; i >= 1; --i)
    {
        instr[i] = '0' + imm % 2; /* take the num */
        imm /= 2;
    }
    /* imm11 */
    instr[11] = '0' + imm % 2; /* take the num */
    imm /= 2;
    /* imm12:19 */
    for (i = 19; i >= 12; --i)
    {
        instr[i] = '0' + imm % 2; /* take the num */
        imm /= 2;
    }
}

void offset_change_2(char *instr, int *is_comp, int num)
{
    int imm; /* the immediate in decimal */
    int i;
    char sign; /* instr[0] */
    int bit;   /* time 2's pow */
    int p = 19;
    imm = 0; /* the immediate in decimal */
    sign = instr[0];
    /* 19-12, instr[12:19] */
    for (i = 12; i <= 19; ++i)
    {
        if (sign == '1')
            bit = 1 - (instr[i] - '0'); /* revert */
        else
            bit = instr[i] - '0';
        imm = imm + (bit * pow1(2, p));
        --p;
    }
    /* 11 instr[11] */
    if (sign == '1')
        bit = 1 - (instr[11] - '0'); /* revert */
    else
        bit = instr[11] - '0';
    imm = imm + (bit * pow1(2, p));
    --p;
    /* 10-1 instr[1:10] */
    for (i = 1; i <= 10; ++i)
    {
        if (sign == '1')
            bit = 1 - (instr[i] - '0'); /* revert */
        else
            bit = instr[i] - '0';
        imm = imm + (bit * pow1(2, p));
        /*  // printf("i = %d, bit = %d, p = %d, imm = %d\n", i, bit, p, imm); */
        --p;
    }
    if (sign == '1') /* revert */
        imm += 2;
    /* how many instructions jump */
    imm /= 4;
    if (sign == '1')
    {
        p = 0; /* counter of compressed instrs */
        for (i = num - imm; i < num; ++i)
        {
            if (is_comp[i] == 1) /* find up */
                ++p;
        }
        imm *= 2;
        imm -= p; /* new offset */
    }
    else
    {
        p = 0; /* counter of compressed instrs */
        for (i = num + 1; i < num + imm; ++i)
        {
            if (is_comp[i] == 1) /* find down */
                ++p;
        }
        imm *= 2;
        imm -= p; /* new offset */
    }
    if (sign == '1')
    {
        imm -= 1;
        deci2bin_2(imm, instr); /* convert back */
        /* revert */
        for (i = 1; i < 20; ++i)
            instr[i] = '0' + '1' - instr[i];
    }
    else
    { /* convert back */
        deci2bin_2(imm, instr);
    }
}

void deci2bin(int imm, char *instr)
{
    int i = 0;
    /* imm4:1 */
    for (i = 23; i >= 20; --i)
    {
        instr[i] = '0' + imm % 2; /* take the num */
        imm /= 2;
    }
    /* imm10:5 */
    for (i = 6; i >= 1; --i)
    {
        instr[i] = '0' + imm % 2; /* take the num */
        imm /= 2;
    }
    /* imm11 */
    instr[24] = '0' + imm % 2; /* take the num */
    imm /= 2;
}

void offset_change(char *instr, int *is_comp, int num)
{
    int imm; /* the immediate */
    int i;
    char sign; /* instr[0] */
    int bit;
    int p = 11; /* first pow */
    imm = 0;    /* default */
    sign = instr[0];
    /* 11, instr[24] */
    if (sign == '1')
        bit = 1 - (instr[24] - '0'); /* revert */
    else
        bit = instr[24] - '0';
    imm = imm + (bit * pow1(2, p));
    --p;
    /* 10-9 */
    for (i = 1; i <= 6; ++i)
    {
        if (sign == '1')
            bit = 1 - (instr[i] - '0'); /* revert */
        else
            bit = instr[i] - '0';
        imm = imm + (bit * pow1(2, p));
        /* // printf("i = %d, bit = %d, p = %d, imm = %d\n", i, bit, p, imm); */
        --p;
    }
    /* 4-1 */
    for (i = 20; i <= 23; ++i)
    {
        if (sign == '1')
            bit = 1 - (instr[i] - '0'); /* revert */
        else
            bit = instr[i] - '0';
        imm = imm + (bit * pow1(2, p));
        /* // printf("i = %d, bit = %d, p = %d, imm = %d\n", i, bit, p, imm); */
        --p;
    }
    if (sign == '1')
        imm += 2;
    /* how many instructions jump */
    imm /= 4;
    /* // printf("imm jump instrs = %d\n", imm); */
    if (sign == '1')
    {
        p = 0; /* counter of compressed instrs */
        for (i = num - imm; i < num; ++i)
        {
            if (is_comp[i] == 1)
                ++p;
        }
        /*  // printf("p = %d\n",p); */
        imm *= 2;
        imm -= p; /* new offset */
    }
    else
    {
        p = 0; /* counter of compressed instrs */
        for (i = num; i < num + imm; ++i)
        {
            if (is_comp[i] == 1)
                ++p;
        }
        imm *= 2;
        imm -= p; /* new offset */
    }
    if (sign == '1')
    {
        imm -= 1;
        deci2bin(imm, instr); /* convert to binary string */
        /* revert */
        for (i = 1; i < 7; ++i)
            instr[i] = '0' + '1' - instr[i]; /* revert */
        for (i = 20; i < 25; ++i)
            instr[i] = '0' + '1' - instr[i]; /* revert */
    }
    else
    {
        deci2bin(imm, instr); /* convert to binary string */
    }
    /*  // printf("%s\n", instr); */
}
