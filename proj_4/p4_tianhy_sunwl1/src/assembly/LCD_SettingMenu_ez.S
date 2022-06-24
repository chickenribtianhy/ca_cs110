.data
    string1: .string "Setting" # "Setting"
    string2: .string "easy" # "easy"
    string3: .string "hard" # "hard"
.section .text # .text
.globl LCD_SettingMenu_ez # LCD_SettingMenu_ez
.type LCD_SettingMenu_ez, @function # LCD_SettingMenu_ez
LCD_SettingMenu_ez:

addi sp,sp,-4 # sp = sp - 4
sw ra, 0(sp) # store ra in stack

li a0 , 50 # a0 = 50
li a1 , 20 # a1 = 20
la a2 , string1 # a2 = string1
li a3 , 0x4416 # a3 = 0x4416
call LCD_ShowString # LCD_ShowString(a0,a1,a2,a3)

li a0, 30 # a0 = 30
li a1, 45 # a1 = 45
la a2, string2 # a2 = string2
li a3, 0x4416 # a3 = 0x4416
call LCD_ShowString # LCD_ShowString(a0,a1,a2,a3)

li a0, 87 # a0 = 87
li a1, 45 # a1 = 45
la a2, string3 # a2 = string3
li a3, 0x4416 # a3 = 0x4416
call LCD_ShowString # LCD_ShowString(a0,a1,a2,a3)

li a0, 30 # a0 = 30
li a1, 65 # a1 = 65
li a2, 60 # a2 = 60
li a3, 65 # a3 = 65
li a4, 0x4416 # a4 = 0x4416
call LCD_DrawLine # LCD_DrawLine(a0,a1,a2,a3,a4)

li a0, 87 # a0 = 87
li a1, 65 # a1 = 65
li a2, 117 # a2 = 117
li a3, 65 # a3 = 65
li a4, 0x0000 # a4 = 0x0000
call LCD_DrawLine # LCD_DrawLine(a0,a1,a2,a3,a4)

lw ra, 0(sp) # restore ra from stack
addi sp, sp, 4 # sp = sp + 4
ret # return