# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S

.text  # code starts here

.globl main
main:
    la a2 str1
    la a3 str2
    lw a4 len1
    lw a5 len2

    jal ra func     # the main calculating function

    add a1 a0 x0    # move the return argument
    li a0 1
    ecall       # print the answer
    li a0 10
    ecall   # exit

func:
    addi sp, sp, -24
	sw s1, 0(sp)    # caller save s1
	sw s2, 4(sp)    # caller save s2
	sw s4, 8(sp)    # caller save s4
	sw s5, 12(sp)   # caller save s5
	sw s6, 16(sp)   # caller save s6
	sw s7, 20(sp)   # caller save s7
    addi sp sp -4
    sw ra 0(sp)     # save the return adress, since it would be changed in following function calls
    jal ra initialization   # preparation
    jal ra dp   # calculation process
    jal ra clear_stack  # clear the dp array on the stack, to get ra
    lw ra 0(sp)     # get the ra for func back from stack
    addi sp sp 4
    lw s1, 0(sp)    # caller load s1
	lw s2, 4(sp)    # caller load s1
	lw s4, 8(sp)    # caller load s1
	lw s5, 12(sp)   # caller load s1
	lw s6, 16(sp)   # caller load s1
	lw s7, 16(sp)   # caller load s1
	addi sp, sp, 24
    jr ra

initialization:
    # initial a dp array on stack, which is of size (len2+1)
    addi a6 sp -8   # a6 is the pointer to dp the array
    addi sp sp -4   # for dp[0]
    sw x0 0(sp)
    add t1 a6 x0    # t1 is the pointer to dp[i]
    li t2 0         # t2 is the number of iterations
    initial_loop:
        bgt t2 a5 initial_exit # if t2 >str2 then initial_exit
        addi sp sp -4 # in each iteration move the stack pointer
        sw x0 0(t1) # initialize dp[t2] to 0, in the stack
        addi t2 t2 1
        addi t1 t1 -4   # move of stack
        jal x0 initial_loop
    initial_exit:
    jr ra

clear_stack:
    add t1 a6 x0    # t1 is the pointer to dp[i]
    li t2 0         # t2 is the number of iterations
    clear_loop:
        bgt t2 a5 clear_exit # if t2 >len2 then initial_exit
        addi sp sp 4 # in each iteration move the stack pointer
        addi t2 t2 1
        jal x0 clear_loop
    clear_exit:
    addi sp sp 4    # clear dp[0] on stack
    jr ra

dp:
    li t0 0 # t0 is the greatest length 
    li t2 1 # t2 is the number of outer iteration
    add s1 a2 x0 # s1 denotes str1[i]
    li s4 0 # s4 for saving dp[j-1]
    outer_loop:     # for (int i = 1; i <= len1; ++i)
        bgt t2 a4 outer_exit
        add t4 a6 x0    # a6 is the pointer the dp, and t4 is the pointer to dp[j]
        li t3 1 # t3 is the number of inner iteration
        add s2 a3 x0 # s2 denotes str2[j]
        lw s6 0(s1)     # s6 is str1[i]
        inner_loop:     # for (int j = 1; j <= len2; ++j)
            bgt t3 a5 inner_exit
            lw s7 0(s2)     # s7 is str2[j]
            addi s5 s4 1    # tmp = save + 1;
            lw s4 0(t4)
            bne s6 s7 exit_matching
                # addi t5 t4 4    
                # since t4 points to dp[j], t5 points to dp[j-1]
                sw s5 0(t4)     # dp[j] = tmp;
                blt s5 t0 less
                    # greater length found
                    add t0 s5 x0    # t0 = dp[j];
                less:
                # sw x0 0(t4)
            exit_matching:
            beq s6 s7 else  # this is an else of last if branch
                sw x0 0(t4) # dp[j] = 0;
            else:
            addi t4 t4 -4   # dp in stack
            addi s2 s2 4    # str2 in static
            addi t3 t3 1    # iter j
            jal x0 inner_loop
        inner_exit:
        addi s1 s1 4    # str1 in static
        addi t2 t2 1    # iter i
        jal x0 outer_loop
    outer_exit:
    add a0 t0 x0    # move the length to a0
    jr ra