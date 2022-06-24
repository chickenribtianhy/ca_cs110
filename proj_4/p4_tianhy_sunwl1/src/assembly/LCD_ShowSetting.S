.data
    string1: .string "Dino!" #"Dino!"
    string2: .string "Play" #"Play"
    string3: .string "Setting" #"Setting"
.section .text #.text
.globl LCD_ShowSetting #LCD_ShowSetting
.type LCD_ShowSetting, @function #LCD_ShowSetting
LCD_ShowSetting: 

addi sp,sp,-4 #sp = sp - 4
sw ra, 0(sp) #store ra in stack
li a0 , 62 #a0 = 62
li a1 , 20 #a1 = 20
la a2 , string1 #a2 = string1
li a3 , 0x4416 #a3 = 0x4416
call LCD_ShowString #call LCD_ShowString

li a0, 30 #a0 = 30
li a1, 45 #a1 = 45
la a2, string2 #a2 = string2
li a3, 0x4416 #a3 = 0x4416
call LCD_ShowString #call LCD_ShowString 

li a0, 87 #a0 = 87
li a1, 45 #a1 = 45
la a2, string3 #a2 = string3
li a3, 0x4416 #a3 = 0x4416
call LCD_ShowString #call LCD_ShowString

li a0, 87 #a0 = 87
li a1, 65 #a1 = 65
li a2, 145 #a2 = 145
li a3, 65 #a3 = 65
li a4, 0x4416 #a4 = 0x4416
call LCD_DrawLine #call LCD_DrawLine

li a0, 30 #a0 = 30
li a1, 65 #a1 = 65
li a2, 60 #a2 = 60
li a3, 65 #a3 = 65
li a4, 0x0000 #a4 = 0x0000
call LCD_DrawLine #call LCD_DrawLine


lw ra, 0(sp) #load ra from stack
addi sp, sp, 4 #sp = sp + 4
ret #ret