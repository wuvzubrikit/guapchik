%include "io.inc"

section .text
global CMAIN
CMAIN:
    xor ecx, ecx        ;Clearing counter c
    lea ebx, [array]    ;Loading adress of the first element
    mov edi, arrayLen   ;Loading array's length l
    mov esi, 0          ;Setting first index i
Iteration:
    cmp esi, edi    
    je End              ;if i=l: jump to End
    mov al, [ebx+esi]   ;al = array[i]
    cmp al, 0       
    jge Increment        ;if array[i] >= 0: inc(i), repeat Iteration
    inc ecx             ;inc(c)
    inc esi             ;inc(i)
    jmp Iteration            ;repeat Iteration
Increment:
    inc esi
    jmp Iteration
End:
    PRINT_DEC 1, ecx    ;Printing counter
    ret
    
section .data
array: db 1, -2, 3, -4, 0
arrayLen:  equ $-array