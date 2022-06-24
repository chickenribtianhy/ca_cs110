#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compression.h"
#include "utils.h"

/* Your code here... */

/*judge if the register is x8-x15*/
int ifregular(char x1, char x2)
{
    /*the first bit is 0 and the second bit is 1 it is x8-x15*/
    if (x1 == '0' && x2 == '1')
        return 1;
    /*if it is not x8-x15, it is not a regular register*/
    else
        return 0;
}
/* for testing */
void print_from_to(char *instr, int index, int num)
{
    /*test the char in the instr*/
    for (; index <= num; index++)
    {
        printf("%c ", instr[index]);
    }
    /*make the test clear*/
    printf("\n");
}

int is_compressible(char *instr)
{
    /*the last 7 bit is 0110011 it is R type*/
    if (instr[31] == '1' && instr[30] == '1' && instr[29] == '0' && instr[28] == '0' && instr[27] == '1' && instr[26] == '1' && instr[25] == '0')
    {
        /*the 17th bit to the 19th bit is 000 it is add or sub*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
        {
            /*the 1st bit is 0 it is add*/
            if (instr[1] == '0')
            {
                /*judge if it is valid to compress*/
                if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
                    return 0; /* it is not valid because rd=0 */
                if (instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
                    return 0; /* it is not valid because rs2=0 */
                else
                {
                    /*if rs1 equals rd it is c.add*/
                    if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    {
                        /*it can be compressed*/
                        return 1;
                    }
                    /* if rs1=0, then c.mv */
                    else if (instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0')
                        return 1;
                    /*else it can't be compressed*/
                    else
                        return 0;
                }
            }
            /*the 1st bit is 1 it is sub*/
            if (instr[1] == '1')
            {
                /*judge if the register in sub is regular register*/
                if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                    /*rs1 and rs2 must be same*/
                    if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                        /*it can be compressed*/
                        return 1;
                    else
                        /*it can't be compressed*/
                        return 0;
                else
                    /*all other can't be compressed*/
                    return 0;
            }
        }
        /*17-19th bit is 111 it is and*/
        if (instr[17] == '1' && instr[18] == '1' && instr[19] == '1')
        {
            /*judge if the register in and is regular register*/
            if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                /*the register must be same in the and*/
                if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    /*it can be compressed*/
                    return 1;
                else
                    /*it can't be compressed*/
                    return 0;
            else
                /*all other can't be compressed*/
                return 0;
        }
        /*17-19th bit is 110 it is or*/
        if (instr[17] == '1' && instr[18] == '1' && instr[19] == '0')
        {
            /*judge if the register is regular register*/
            if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                /*the register must be same in the or*/
                if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    /*it can be compressed*/
                    return 1;
                else
                    /*it can't be compressed*/
                    return 0;
            else
                /*all other can't be compressed*/
                return 0;
        }
        /*17-19th bit is 100 it is xor*/
        if (instr[17] == '1' && instr[18] == '0' && instr[19] == '0')
        {
            /*judge if the register is regular register*/
            if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                /*register must be same in the xor*/
                if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    /*it can be compressed*/
                    return 1;
                else
                    return 0; /*it can't be compressed*/
            else
                return 0; /*all other can't be compressed*/
        }
    }

    /*the last 7 bit is 1100111 it is the first I type (jalr)*/
    if (instr[25] == '1' && instr[26] == '1' && instr[27] == '0' && instr[28] == '0' && instr[29] == '1' && instr[30] == '1' && instr[31] == '1')
    {
        if (!(instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0'))
            return 0;
        /*rs1=0*/
        if (instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0')
            return 0;
        /*jalr:x0,0(rs1) c.jr*/
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
            return 1;
        /*00001 can be compressed*/
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '1')
            return 1;
        else
            return 0; /*all other can't be compressed*/
    }

    /*the last 7 bit is 0010011 it is the second I type*/
    if (instr[25] == '0' && instr[26] == '0' && instr[27] == '1' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        /*17-19th bit is 000 it is addi*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
        {
            /*rd=x0*/
            if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
                return 0;
            else /*rd is not equal to 0*/
            {
                /* imm[11:5] must all be sign extension */
                if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1' && instr[6] == '1')))
                    return 0;
                /*12-16th bit(rs1) is x0 c.li*/
                if (instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0')
                    return 1;
                /*in addi rd and rs1 must be same*/
                else if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                {
                    /*judge if it is a none zero immediate*/
                    if (instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
                        return 0;
                    else
                        return 1; /*else can be compressed*/
                }
                else
                    return 0; /*all other can't be compressed*/
            }
        }

        /*17-19th bit is 001 it is slli*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '1')
        {
            /*rd=x0*/
            if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
                return 0;
            /*shamt[5] is not equal to 0*/
            else if (instr[6] != '0')
                return 0;
            else /*judge*/
            {
                /*in slli rd and rs1 must be same*/
                if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    return 1;
                else
                    return 0; /*else can't be compressed*/
            }
        }

        /*17-19th bit is 111 it is andi*/
        if (instr[17] == '1' && instr[18] == '1' && instr[19] == '1')
        {
            /*judge if rd and rs1 are regular register*/
            if (ifregular(instr[12], instr[13]) == 0)
                return 0;
            else if (ifregular(instr[20], instr[21]) == 0) /*judge if rs1 is a regular register*/
                return 0;
            else /*judge*/
            {
                /* imm[11:5] must all be sign extension */
                if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1' && instr[6] == '1')))
                    return 0;
                /*in andi rd and rs1 must be same*/
                if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    return 1;
                else
                    return 0; /*else can't be compressed*/
            }
        }

        /*17-19th bit is 101 it is srli or srai*/
        if (instr[17] == '1' && instr[18] == '0' && instr[19] == '1')
        {
            /*the second bit is 0 it is srli*/
            if (instr[1] == '0')
            {
                /*in srli shamt[5] must be 0*/
                if (instr[6] != '0')
                    return 0; /*if it is 0 it can't be compressed*/
                else
                {
                    /*judge if rd and rs1 are regular register*/
                    if (ifregular(instr[12], instr[13]) == 0)
                        return 0;
                    else if (ifregular(instr[20], instr[21]) == 0) /*judge if rs1 is a regular register*/
                        return 0;
                    else /*judge*/
                    {
                        /*in srli rd and rs1 must be same*/
                        if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                            return 1;
                        else
                            return 0; /*else can't be compressed*/
                    }
                }
            }
            /*the second bit is 1 it is srai*/
            else
            {
                /*in srai shamt[5] must be 0*/
                if (instr[6] != '0')
                    return 0; /*if it is 0 it can't be compressed*/
                else
                {
                    /*judge if rd and rs1 are regular register*/
                    if (ifregular(instr[12], instr[13]) == 0)
                        return 0;
                    else if (ifregular(instr[20], instr[21]) == 0) /*judge if rs1 is a regular register*/
                        return 0;
                    else /*judge*/
                    {
                        /*in srai rd and rs1 must be same*/
                        if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                            return 1;
                        else
                            return 0; /*else can't be compressed*/
                    }
                }
            } /**/
        }
    }

    /*the last 7 bit is 0000011 it is the third I type*/
    if (instr[25] == '0' && instr[26] == '0' && instr[27] == '0' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        /* imm[11:5] must all be sign extension */
        /* if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1')))
            return 0; */
        if (!(instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0'))
            return 0;
        /*judge if the rd and rs1 is regular register*/
        if (ifregular(instr[12], instr[13]) == 0)
        {
            return 0; /*it can't be compressed*/
        }
        else if (ifregular(instr[20], instr[21]) == 0) /*judge if the rs1 is a regular register*/
        {
            return 0; /*it can't be compressed*/
        }
        else if (instr[10] != '0' || instr[11] != '0')
            return 0;
        /*c.lw*/
        else if (instr[17] == '0' && instr[18] == '1' && instr[19] == '0')
        {
            return 1; /*it can be compressed*/
        }
    }

    /*the last 7 bit is 0110111 it is U type*/
    if (instr[25] == '0' && instr[26] == '1' && instr[27] == '1' && instr[28] == '0' && instr[29] == '1' && instr[30] == '1' && instr[31] == '1')
    {
        /* imm[31:17] must all be sign extension */
        if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0' && instr[12] == '0' && instr[13] == '0' && instr[14] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1' && instr[6] == '1' && instr[7] == '1' && instr[8] == '1' && instr[9] == '1' && instr[10] == '1' && instr[11] == '1' && instr[12] == '1' && instr[13] == '1' && instr[14] == '1')))
            return 0;
        /*judge if rd=x0 or rd=x2*/
        if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
            return 0;
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '1' && instr[24] == '0') /*00010 can't be compressed*/
            return 0;
        else
        {
            /*judge if the immediate is zero*/
            if (instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0' && instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0' && instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
                return 0;
            /*c.lui*/
            else
                return 1; /*it can be compressed*/
        }
    }

    /*the last 7 bit is 0100011 it is S type*/
    if (instr[25] == '0' && instr[26] == '1' && instr[27] == '0' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        if (!(instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0'))
            return 0;
        /*judge if rs1 is a regular register*/
        if (ifregular(instr[12], instr[13]) == 0)
            return 0;
        else if (ifregular(instr[20], instr[21]) == 0) /*judge if rs1 is a regular register*/
            return 0;
        else if (instr[23] != '0' || instr[24] != '0') /*it should be multipy of 4*/
            return 0;
        else
            return 1;
    }

    /*the last 7 bit is 1100011 it is B type*/
    if (instr[25] == '1' && instr[26] == '1' && instr[27] == '0' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        /* imm[12:8] */
        /* if (!((instr[24] == '0' && instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0') || (instr[24] == '1' && instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1')))
            return 0; */
        /*17-19th bit is 000 it is beq*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
        {
            /*judge if the rs2 is x0*/
            if (instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
            {
                /*judge if rs1 is a regular register*/
                if (ifregular(instr[12], instr[13]) == 0)
                    return 0;
                else
                    return 1; /*it can be compressed*/
            }
            /*rs2 is not equal to x0*/
            else
                return 0;
        }
        /*17-19th bit is 001 it is bne*/
        else if (instr[17] == '0' && instr[18] == '0' && instr[19] == '1')
        {
            /*judge if the rs2 is x0*/
            if (instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
            {
                /*judge if rs1 is a regular register*/
                if (ifregular(instr[12], instr[13]) == 0)
                    return 0;
                else
                    return 1; /*it can be compressed*/
            }
            /*rs2 is not equal to x0*/
            else
                return 0;
        }
        else
            return 0;
    } /**/

    /*the last 7 bit is 1101111 it is J type*/
    if (instr[25] == '1' && instr[26] == '1' && instr[27] == '0' && instr[28] == '1' && instr[29] == '1' && instr[30] == '1' && instr[31] == '1')
    {
        /*judge if rd is x0*/
        if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
            return 1;
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '1')
            return 1; /*it can be compressed*/
        else
            return 0; /*it can't be compressed*/
    }
    return 0; /*all other can't be compressed*/
}

/* ============================================================================================================================== */
/* ============================================================================================================================== */
/* ============================================================================================================================== */

int compress_instr(char *instr, char *c_instr, int *is_comp, int num)
{
    /*the last 7 bit is 0110011 it is R type*/
    if (instr[31] == '1' && instr[30] == '1' && instr[29] == '0' && instr[28] == '0' && instr[27] == '1' && instr[26] == '1' && instr[25] == '0')
    {
        /*the 17th bit to the 19th bit is 000 it is add or sub*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
        {
            /*the 1st bit is 0 it is add*/
            if (instr[1] == '0')
            {
                /*judge if it is valid to compress*/
                if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
                    return 0; /* it is not valid because rd=0 */
                if (instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
                    return 0; /* it is not valid because rs2=0 */
                else
                {
                    /*if rs1 equals rd it is c.add*/
                    if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    {
                        return add_compress(instr, c_instr); /*return add compress*/
                    }
                    /* if rs1=0, then c.mv */
                    else if (instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0')
                        return mv_compress(instr, c_instr); /*return mv compress*/
                    else
                        return 0; /*all other can't be compressed*/
                }
            }
            /*the 1st bit is 1 it is sub*/
            if (instr[1] == '1')
            {
                /*judge if the register is a regular register*/
                if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                    if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24]) /*register must be same*/
                        return sub_compress(instr, c_instr);
                    else
                        return 0; /*else can't be compressed*/
                else
                    return 0; /*else can't be compressed*/
            }
        }
        /*17-19th bit is 111 it is and*/
        if (instr[17] == '1' && instr[18] == '1' && instr[19] == '1')
        {
            /**/
            if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    return and_compress(instr, c_instr); /* turn to and */
                else
                    return 0; /* else can't be compressed */
            else
                return 0;
        }
        /*17-19th bit is 110 it is or*/
        if (instr[17] == '1' && instr[18] == '1' && instr[19] == '0')
        {
            /*judge if the register is a regular register*/
            if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24]) /*register must be same*/
                    return or_compress(instr, c_instr);                                         /*return or compress*/
                else
                    return 0; /*else can't be compressed*/
            else
                return 0;
        }
        /*17-19th bit is 100 it is xor*/
        if (instr[17] == '1' && instr[18] == '0' && instr[19] == '0')
        {
            /*judge if the register is a regular register*/
            if (ifregular(instr[7], instr[8]) != 0 && ifregular(instr[12], instr[13]) != 0 && ifregular(instr[20], instr[21]) != 0)
                if (instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24]) /*the register must be same*/
                    return xor_compress(instr, c_instr);                                        /*return xor compress*/
                else
                    return 0; /*else can't be compressed*/
            else
                return 0; /*else can't be compressed*/
        }
    }

    /*the last 7 bit is 1100111 it is the first I type (jalr)*/
    if (instr[25] == '1' && instr[26] == '1' && instr[27] == '0' && instr[28] == '0' && instr[29] == '1' && instr[30] == '1' && instr[31] == '1')
    {
        if (!(instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0'))
            return 0;
        /*rs1=0*/
        if (instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0')
            return 0;
        /*jalr:x0,0(rs1) c.jr*/
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
            return jr_compress(instr, c_instr); /*return jr compress*/
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '1')
            return jalr_compress(instr, c_instr); /*return jalr compress*/
        else
            return 0; /*else can't be compressed*/
    }

    /*the last 7 bit is 0010011 it is the second I type*/
    if (instr[25] == '0' && instr[26] == '0' && instr[27] == '1' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        /*17-19th bit is 000 it is addi*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
        {
            /*rd=x0*/
            if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
                return 0;
            else /*rd is not equal to 0*/
            {
                /* imm[11:5] must all be sign extension */
                if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1' && instr[6] == '1')))
                    return 0;
                /*12-16th bit(rs1) is x0 c.li*/
                if (instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0')
                    return li_compress(instr, c_instr);
                /*in addi rd and rs1 must be same*/
                else if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                {
                    /*judge if it is a none zero immediate*/
                    if (instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
                        return 0;
                    else
                        return addi_compress(instr, c_instr); /*return addi compress*/
                }
                else
                    return 0; /*else can't be compressed*/
            }
        }

        /*17-19th bit is 001 it is slli*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '1')
        {
            /*rd=x0*/
            if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
                return 0;
            /*shamt[5] is not equal to 0*/
            else if (instr[6] != '0')
                return 0;
            else /*judge*/
            {
                /*in slli rd and rs1 must be same*/
                if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    return slli_compress(instr, c_instr); /*return slli compress*/
                else
                    return 0; /*else can't be compressed*/
            }
        }

        /*17-19th bit is 111 it is andi*/
        if (instr[17] == '1' && instr[18] == '1' && instr[19] == '1')
        {
            /*judge if rd and rs1 are regular register*/
            if (ifregular(instr[12], instr[13]) == 0)
                return 0;
            else if (ifregular(instr[20], instr[21]) == 0) /*judge if the register is a regular register*/
                return 0;
            else
            {
                /* imm[11:5] must all be sign extension */
                if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1' && instr[6] == '1')))
                    return 0; /*else can't be compressed*/
                /*in andi rd and rs1 must be same*/
                if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                    return andi_compress(instr, c_instr); /*return andi compress*/
                else
                    return 0; /*else can't be compressed*/
            }
        }

        /*17-19th bit is 101 it is srli or srai*/
        if (instr[17] == '1' && instr[18] == '0' && instr[19] == '1')
        {
            /*the second bit is 0 it is srli*/
            if (instr[1] == '0')
            {
                /*in srli shamt[5] must be 0*/
                if (instr[6] != '0')
                    return 0;
                else /*judge*/
                {
                    /*judge if rd and rs1 are regular register*/
                    if (ifregular(instr[12], instr[13]) == 0)
                        return 0;
                    else if (ifregular(instr[20], instr[21]) == 0) /*judge if the register is a regular register*/
                        return 0;                                  /*else can't be compressed*/
                    else
                    {
                        /*in srli rd and rs1 must be same*/
                        if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                            return srli_compress(instr, c_instr); /*return srli compress*/
                        else
                            return 0; /*else can't be compressed*/
                    }
                }
            }
            /*the second bit is 1 it is srai*/
            else
            {
                /*in srai shamt[5] must be 0*/
                if (instr[6] != '0')
                    return 0;
                else
                {
                    /*judge if rd and rs1 are regular register*/
                    if (ifregular(instr[12], instr[13]) == 0)
                        return 0;
                    else if (ifregular(instr[20], instr[21]) == 0) /*judge if the register is a regular register*/
                        return 0;
                    else
                    {
                        /*in srai rd and rs1 must be same*/
                        if (instr[12] == instr[20] && instr[13] == instr[21] && instr[14] == instr[22] && instr[15] == instr[23] && instr[16] == instr[24])
                            return srai_compress(instr, c_instr); /*return srai compress*/
                        else
                            return 0; /*else can't be compressed*/
                    }
                }
            } /**/
        }
    }

    /*the last 7 bit is 0000011 it is the third I type*/
    if (instr[25] == '0' && instr[26] == '0' && instr[27] == '0' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        /* imm[11:6] must all be sign extension */
        /* if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1')))
            return 0; */
        if (!(instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0'))
            return 0;
        /*judge if the rd and rs1 is regular register*/
        if (ifregular(instr[12], instr[13]) == 0)
            return 0;
        else if (ifregular(instr[20], instr[21]) == 0) /*judge if the register is a regular register*/
            return 0;
        else if (instr[10] != '0' || instr[11] != '0') /*judge the last two bit is 0*/
            return 0;
        /*c.lw*/
        else if (instr[17] == '0' && instr[18] == '1' && instr[19] == '0')
            return lw_compress(instr, c_instr); /*return lw compress*/
    }

    /*the last 7 bit is 0110111 it is U type*/
    if (instr[25] == '0' && instr[26] == '1' && instr[27] == '1' && instr[28] == '0' && instr[29] == '1' && instr[30] == '1' && instr[31] == '1')
    {
        /* imm[31:17] must all be sign extension */
        if (!((instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0' && instr[12] == '0' && instr[13] == '0' && instr[14] == '0') || (instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1' && instr[4] == '1' && instr[5] == '1' && instr[6] == '1' && instr[7] == '1' && instr[8] == '1' && instr[9] == '1' && instr[10] == '1' && instr[11] == '1' && instr[12] == '1' && instr[13] == '1' && instr[14] == '1')))
            return 0;
        /*judge if rd=x0 or rd=x2*/
        if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
            return 0;
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '1' && instr[24] == '0')
            return 0; /*it can't be compressed*/
        else
        {
            /*judge if the immediate is zero*/
            if (instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0' && instr[5] == '0' && instr[6] == '0' && instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0' && instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0' && instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
                return 0; /*else can't be compressed*/
            /*c.lui*/
            else
                return lui_compress(instr, c_instr); /*return lui compress*/
        }
    }

    /*the last 7 bit is 0100011 it is S type*/
    if (instr[25] == '0' && instr[26] == '1' && instr[27] == '0' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        if (!(instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0' && instr[4] == '0'))
            return 0;
        /*judge if rs1 is a regular register*/
        if (ifregular(instr[12], instr[13]) == 0)
            return 0;
        else if (ifregular(instr[20], instr[21]) == 0) /*judge if the register is a regular register*/
            return 0;
        else if (instr[23] != '0' || instr[24] != '0') /*the last two bit is 0*/
            return 0;
        else
            return sw_compress(instr, c_instr); /*return sw compress*/
    }

    /*the last 7 bit is 1100011 it is B type*/
    if (instr[25] == '1' && instr[26] == '1' && instr[27] == '0' && instr[28] == '0' && instr[29] == '0' && instr[30] == '1' && instr[31] == '1')
    {
        offset_change(instr, is_comp, num);
        /* imm[12:8] */
        /* if (!((instr[24] == '0' && instr[0] == '0' && instr[1] == '0' && instr[2] == '0' && instr[3] == '0') || (instr[24] == '1' && instr[0] == '1' && instr[1] == '1' && instr[2] == '1' && instr[3] == '1')))
            return 0; */
        /*17-19th bit is 000 it is beq*/
        if (instr[17] == '0' && instr[18] == '0' && instr[19] == '0')
        {
            /*judge if the rs2 is x0*/
            if (instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
            {
                /*judge if rs1 is a regular register*/
                if (ifregular(instr[12], instr[13]) == 0)
                    return 0; /*else can't be compressed*/
                else
                    return beq_compress(instr, c_instr); /*return beq_compress*/
            }
            /*rs2 is not equal to x0*/
            else
                return 0;
        }
        /*17-19th bit is 001 it is bne*/
        else if (instr[17] == '0' && instr[18] == '0' && instr[19] == '1')
        {
            /*judge if the rs2 is x0*/
            if (instr[7] == '0' && instr[8] == '0' && instr[9] == '0' && instr[10] == '0' && instr[11] == '0')
            {
                /*judge if rs1 is a regular register*/
                if (ifregular(instr[12], instr[13]) == 0)
                    return 0;
                else
                    return bne_compress(instr, c_instr); /*return bne compress*/
            }
            /*rs2 is not equal to x0*/
            else
                return 0;
        }
        return 0;
    } /**/

    /*the last 7 bit is 1101111 it is J type*/
    if (instr[25] == '1' && instr[26] == '1' && instr[27] == '0' && instr[28] == '1' && instr[29] == '1' && instr[30] == '1' && instr[31] == '1')
    {
        offset_change_2(instr, is_comp, num);
        /* imm[20:11] */
        /* if (!((instr[0] == '0' && instr[12] == '0' && instr[13] == '0' && instr[14] == '0' && instr[15] == '0' && instr[16] == '0' && instr[17] == '0' && instr[18] == '0' && instr[19] == '0' && instr[11] == '0') || (instr[0] == '1' && instr[12] == '1' && instr[13] == '1' && instr[14] == '1' && instr[15] == '1' && instr[16] == '1' && instr[17] == '1' && instr[18] == '1' && instr[19] == '1' && instr[11] == '1')))
            return 0; */
        /*judge if rd is x0*/
        if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '0')
            return j_compress(instr, c_instr); /*return j compress*/
        else if (instr[20] == '0' && instr[21] == '0' && instr[22] == '0' && instr[23] == '0' && instr[24] == '1')
            return jal_compress(instr, c_instr); /*return jal compress*/
        else
            return 0; /*else can't be compressed*/
    }
    return 0;
}