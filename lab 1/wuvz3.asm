%include "io.inc"

;The program checks if a triangle is isosceles 
;1 for True
;0 for False

section .text
global CMAIN        
CMAIN:
    mov al, [a]
    mov bl, [b]
    cmp al, bl
    je YES
    
    cmp al, [c]
    je YES 
    
    cmp bl, [c]
    je YES
    
    PRINT_DEC 4, 0
    ret
YES: 
    PRINT_DEC 4, 1
    ret

section .data
a db 1
b db 2
c db 1