.data

# Constant integer specifying the lines of RVC codes

# DO NOT MODIFY THIS VARIABLE
.globl lines_of_rvc_codes
lines_of_rvc_codes:
    .word 1


# RVC codes, 16-bits instructions mixed with 32-bits instructions
# A 16/32-bits binary number represents one line of rvc code.
# You can suppose all of the input codes are valid. 

# DO NOT MODIFY THIS VARIABLE
.globl rvc_codes
rvc_codes:
    # .word 0b00000000000000000000001010110011
    # .half 0b0001010111111101
    # .half 0b1001001010101010
    # .half 0b0001010111111101
    # .word 0b11111110000001011101111011100011
    # .half 0b1000010100010110
    # .half 0b1000000010000010
    # .half 0b1000111001110101
    # .half 0b0110001010100001
    # .half 0b1100011011010000
    # .half 0b0010000000011001
    # .half 0b1000000100000101
    # .half 0b1011111111100101
    # .half 0b0000000111111001

    # .half 0b1100011011010000

    # .word 0b00000000100101010010001110100011

    # .word 0b00000001010000110000001010010011
    # .half 0b0110001010100001
    # .half 0b0000001100101110
    # .word 0b00000000101100110101001100010011
    # .half 0b1001100001000101
    # .half 0b1101100001101101

    .word 0b00000000100000111110001100110011


