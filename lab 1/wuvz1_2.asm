%include "io.inc"

;a /(b-c)
;test = {-4, -22, 6}

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
a db 0xFC ; two’s complement of -4
b db 0xEA ; two’s complement of -22
c db 0x06 ; two’s complement of 6