#   Project 1.2 RVC instructions to RISC-V instructions in RISC-V

#   You can suppose you will get the number of machine codes you should translate from 
#   "lines_of_rvc_codes" and get the 16 or 32 bits-machine codes from "rvc_codes". 
#   Both of them are stored in file "input.S"

#   When we test your project, we will change the input files content.

# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S

# Your code to convert the RVC codes to RVI codes.

# Exit with error code 0
add	   a1, x0, x0
addi   a0, x0, 17
ecall