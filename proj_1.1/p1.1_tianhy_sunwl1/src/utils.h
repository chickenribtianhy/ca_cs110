#ifndef UTILS_H
#define UTILS_H

/* Your code here... */

int add_compress(char *instr, char *c_instr);

int mv_compress(char *instr, char *c_instr);

int sub_compress(char *instr, char *c_instr);

int and_compress(char *instr, char *c_instr);

int or_compress(char *instr, char *c_instr);

int xor_compress(char *instr, char *c_instr);

int jr_compress(char *instr, char *c_instr);

int jalr_compress(char *instr, char *c_instr);

int li_compress(char *instr, char *c_instr);

int addi_compress(char *instr, char *c_instr);

int slli_compress(char *instr, char *c_instr);

int andi_compress(char *instr, char *c_instr);

int srli_compress(char *instr, char *c_instr);

int srai_compress(char *instr, char *c_instr);

int lw_compress(char *instr, char *c_instr);

int lui_compress(char *instr, char *c_instr);

int sw_compress(char *instr, char *c_instr);

int beq_compress(char *instr, char *c_instr);

int bne_compress(char *instr, char *c_instr);

int j_compress(char *instr, char *c_instr);

int jal_compress(char *instr, char *c_instr);

void offset_change(char *instr, int *is_comp, int num);

void offset_change_2(char *instr, int *is_comp, int num);

#endif