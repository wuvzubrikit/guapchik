%include "io.inc"

;a /(b-c)
;test = {10,26,27}

section .text
global CMAIN
CMAIN:  
    xor ah, ah          ;Preparing AX for division
    mov al, [a]
    mov bl, [b] 
    sub bl, [c]         ;b-c
    idiv bl             ;a / (b-c)
    
    PRINT_DEC 4, al     ;a div (b-c)
    NEWLINE
    PRINT_DEC 4, ah     ;a mod (b-c)
    ret
    
section .data
a db 0x0A ; two’s complement of 10
b db 0x1A ; two’s complement of 26
c db 0x1B ; two’s complement of 27