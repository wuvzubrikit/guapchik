%include "io.inc"

section .text
global CMAIN
CMAIN:
    lea esi, [array]        ;Loading adress of the first byte
    mov al, [esi]           ;Loading first byte
    and al, 0xF8            ;Masking
    shr al, 3               ;Shifting bits
    PRINT_DEC 1, al         ;Printing first element
    NEWLINE
    
    mov bl, [esi]           ;Loading first byte
    and bl, 0x07            ;Masking first bits of second element
    shl bl, 2               ;Shifting down
    inc esi         
    mov al, [esi]           ;Loading second byte
    and al, 0xC0            ;Masking last bits of second element
    shr al, 6               ;Shifting up
    or al, bl               ;Combinig bits
    PRINT_DEC 1, al         ;Printing second element
    NEWLINE
                            ;Doing the same algorythm over last bytes
    mov al, [esi]
    and al, 0x3E
    shr al, 1
    PRINT_DEC 1, al
    NEWLINE
    
    mov bl, [esi]
    and bl, 0x01
    shl bl, 4
    inc esi
    mov al, [esi]
    and al, 0xF0
    shr al, 4
    or al, bl
    PRINT_DEC 1, al
    NEWLINE
    
    mov bl, [esi]
    and bl, 0x0F
    shl bl, 1
    inc esi
    mov al, [esi]
    and al, 0x80
    shr al, 7
    or al, bl
    PRINT_DEC 1, al
    NEWLINE
    
    mov al, [esi]
    and al, 0x7C
    shr al, 2
    PRINT_DEC 1, al
    NEWLINE
    
    mov bl, [esi]
    and bl, 0x03
    shl bl, 3 
    inc esi
    mov al, [esi]
    and al, 0xE0
    shr al, 5
    or al, bl
    PRINT_DEC 1, al
    NEWLINE   
    
    mov al, [esi]
    and al, 0x1F
    PRINT_DEC 1, al
    NEWLINE   
                            
    ret
    
section .data
array: db 0x08, 0x86, 0x42, 0x98, 0xE8

;Packing array by 5 bits:
;1     2     3     4     5     6     7     8
;00001 00010 00011 00100 00101 00110 00111 01000
;00001000 10000110 01000010 10011000 11101000
;0x08     0x86     0x42     0x98     0xE8