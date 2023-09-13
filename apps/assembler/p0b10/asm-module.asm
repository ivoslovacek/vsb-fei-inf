    bits 64

    section .data

    section .text

global str_cp_part
global str_count_numbers
global rect_perimeter

str_cp_part:
    mov r8, -1
    mov r9, 0
    
    mov r9, rcx
    sub r9, rdx

.l1:
    inc r8

    mov r10b, [rsi + r8 * 1]
    mov [rdi + rdx * 1], r10b

    inc rdx
     
    cmp r8, r9
    jnge .l1

    inc r8

    mov byte [rdi + r8 * 1], 0

    ret

str_count_numbers:
    mov rcx, 0
    mov rax, 0
    mov rdx, 0

    mov rcx, -1

.l1:
    inc rcx

    mov dl, [rdi + rcx * 1]

    cmp dl, 48
    jl .l3

    cmp dl, 57
    jg .l3

    inc rax

.l2:
    inc rcx

    mov dl, [rdi + rcx * 1]

    cmp dl, 48
    jl .l3

    cmp dl, 57
    jg .l3
    
    jmp .l2


.l3:

    cmp dl, 0
    jne .l1

    ret

rect_perimeter:
    mov rax, 0

    add eax, edi
    add eax, esi
    shl eax, 1

    ret