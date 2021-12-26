%include "io.inc"     

;a /(b-c)
;test = {-4, -22, 6} 
;(-4) / (-22-6) = 0,14285714

section .text
global CMAIN
CMAIN:
    mov ebp, esp            ;Reversed Polish Notaion:
    fld dword [a]           
    fld dword [b]
    fld dword [c]
    fsub 
    fdiv
    fst dword [result]
    
    PRINT_HEX 4, [result]   ;IEEE754 of the result
    ret
    
section .data
a dd 0xC0800000         ;IEEE754 of -4
b dd 0xC1B00000         ;IEEE754 of -22
c dd 0x40C00000         ;IEEE754 of 6
result dd 0x00000000    ;empty variable