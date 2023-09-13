    bits 64

    section .data

    section .text

global suma_int
global pocet_cislic

suma_int:
    mov rax, 0
    mov eax, edi
    add eax, esi

    ret

pocet_cislic:
    mov rax, 0

.l1:
    cmp [rdi], byte 0
    je .l2

    cmp [rdi], byte '0'
    jl .l3
    
    cmp [rdi], byte '9'
    jg .l3

    inc eax

.l3:

    inc rdi
    jmp .l1

.l2:
    ret