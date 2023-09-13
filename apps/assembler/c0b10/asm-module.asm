    bits 64

    section .data

    section .text

global str_merge_diff
global arr_sum_and_return

global hamm_dist

str_merge_diff:
    mov rcx, 0
    mov rax, 0
    mov r8, 0
    mov r9, 0


.l1:
    mov r8b, [rdi + rcx * 1]
    mov r9b, [rsi + rcx * 1]

    cmp r8b, r9b
    je .l2

    mov [rdx + rax * 1], r8b
    inc rax
    mov [rdx + rax * 1], r9b
    inc rax

.l2:

    inc rcx
    cmp r8b, 0
    jne .l1

;    cmp r9b, 0
;    je .l4 
;
;.l3:
;    mov [rdx + rax * 1], byte ' '
;    inc rax
;    mov [rdx + rax * 1], r9b
;    inc rax
;
;    inc rcx
;    mov r9b, [rsi + rcx * 1]
;
;    cmp r9b, 0
;    jne .l3
;    
;
;.l4:
    mov [rdx + rax * 1], byte 0

    ret


arr_sum_and_return:
    mov r10, 0
    mov rax, 0
    mov r9, 0

.l1:
    add r9, [rdi + r10 * 8]

    cmp rax, [rdi + r10 * 8]
    cmovl rax, [rdi + r10 * 8]

    inc r10
    cmp r10, rsi
    jnge .l1

    mov r10, 0

.l2:
    add r9, [rdx + r10 * 8]

    cmp rax, [rdx + r10 * 8]
    cmovl rax, [rdx + r10 * 8]

    inc r10
    cmp r10, rcx
    jnge .l2

    ret

hamm_dist:
    mov rax, 0
    mov eax, 68
    mov rcx, 0 ; counter
    mov r8, 0 ; 
    mov r9, 0
    mov r10, 0
    mov r11, 0

.l1:
    mov r8d, [rsi + rcx * 4]
    xor r8d, edi

    mov r9, 0
    mov r11, 0

.l2:
    mov r10d, r8d
    and r10d, 0x1
    add r11d, r10d
    shr r8d, 1

    inc r9d
    cmp r9d, 32
    jnge .l2

    cmp eax, r11d
    cmovg eax, r11d

    inc ecx
    cmp ecx, edx
    jnge .l1

    ret