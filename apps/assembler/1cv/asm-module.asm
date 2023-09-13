;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 64

    section .data


    ; variables

    ;global g_some_asm_var
    ;extern g_some_c_var

;g_some_asm_var dd ?

    extern enc_string
    extern decoded
    extern first_extended
    extern last_extended
    extern merged
    
    string: dw "ahoj"

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function

;some_asm_function:
    ;ret

global decode 
global extend_and_merge

decode:

    mov al,  [enc_string + 2]
    mov [decoded + 0], al
    mov al,  [enc_string + 3]
    mov [decoded + 1], al
    mov al,  [enc_string + 1]
    mov [decoded + 2], al
    mov al,  [enc_string + 0]
    mov [decoded + 3], al

    ret



extend_and_merge:

    mov eax, 0
    mov al, [decoded + 0]
    mov [first_extended], eax

    mov eax, 0
    mov al, [decoded + 3]
    mov [last_extended], eax

    mov rsi, [first_extended]
    mov r14, [last_extended]
    mov [merged + 0], rsi
    mov [merged + 4], r14


    test rsi, 0x50
    je _continue

    mov rax, 0x1
    mov rdi, 1
    mov rsi, string
    mov rdx, 4
    syscall

_continue:

    ret
