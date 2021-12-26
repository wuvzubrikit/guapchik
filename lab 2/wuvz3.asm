%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;Insertion sort
    lea esi, [array]        ;Loading adress of the first element
    lea edx, [esi]          ;Storing initial index
    lea edi, [arrayLen+esi] ;Loading array's length l
Iteration:                  ;for i = 1 to l-1
    cmp edi, esi
    je End                  ;if i = l: jump to End
    mov al, [esi]           ;key = array[i]
    mov ebx, esi            ;j = i 
Comparison:
    mov ah, [ebx-1]         ;array[j-1]
    cmp ah, al              ;Checking if array[j-1] > key
    jg IsAbove
    jmp IsLess
IsAbove:
    cmp ebx, edx           
    ja Next                 ;if j>0: continue
    jmp IsLess
IsLess:
    mov [ebx], al           ;array[i] = key
    inc esi                 ;inc(i)
    jmp Iteration
Next:
    mov [ebx], ah           ;array[j] = array[j-1]
    dec ebx                 ;dec(j)
    jmp Comparison

End:
    PRINT_DEC 1, [edx]      ;Printing sorted array
    NEWLINE
    inc edx
    cmp edi, edx
    ja End
    ret  
    
section .data
array: db 35, 12, -8, 47, 0, 31
arrayLen: equ $-array