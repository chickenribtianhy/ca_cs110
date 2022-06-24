.data
	msg: .string "faq again"
.section .text
.globl draw
.type draw, @function
draw:
	# YOUR CODE HERE
addi sp,sp,-4
sw ra, 0(sp)
li a0, 20
mv a1, a0
mv a2, a0
li a3, 0xff9e
call LCD_DrawCircle

li a0, 50
li a1, 0
li a2, 100
li a3, 20
li a4, 0x4810
call LCD_DrawRectangle

li a0, 10
li a1, 50
la a2, msg
li a3, 0x4416
call LCD_ShowString

lw ra, 0(sp)
addi sp, sp, 4
ret