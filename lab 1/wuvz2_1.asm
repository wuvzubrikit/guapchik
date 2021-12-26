%include "io.inc"     

;a /(b-c)
;test = {10, 26, 27} 
;10 / (22-27) = -10

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
a dd 0x41200000         ;IEEE754 of 10
b dd 0x41D00000         ;IEEE754 of 26
c dd 0x41D80000         ;IEEE754 of 27
result dd 0x00000000    ;empty variable