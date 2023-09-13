    bits 64

    section .data

    section .text

global isPalindrom
global gcd
global tribonacci

isPalindrom:
    mov rcx, 0
    mov rax, 0
    mov rdx, 0
    mov rsi, 0
    mov r8, 0
    mov r9, 0

.l1:
    mov r8b, [rdi + rcx * 1]

    inc rcx
    cmp r8b, 0
    jne .l1

    sub rcx, 2
    mov rsi, rcx
    mov rdx, rcx
    shr rdx, 1
    mov rcx, 0

.l2:
    mov r8b, [rdi + rcx * 1]
    mov r9b, [rdi + rsi * 1]

    cmp r8b, r9b
    jne .l3

    dec rsi
    inc rcx
    cmp rcx, rdx 
    jng .l2

    mov eax, 1
    jmp .l4

.l3:
    mov eax, 0

.l4:

    ret

gcd:
    mov rax, 0
    mov r8, 0
    mov r9, 0
    mov rcx, 1

    mov r8d, [rdi]

.startloop:

    mov r9d, [rdi + rcx * 4]

    cmp r8d, r9d
    je .l10

.l1:
    cmp r8d, r9d
    jng .l2 

    sub r8d, r9d

    jmp .l3

.l2:

    sub r9d, r8d

.l3:

    cmp r8d, r9d
    jne .l1

    inc rcx
    cmp ecx, esi
    jnge .startloop


.l10:
    mov eax, r8d

    ret

tribonacci:
    mov r8, 0
    mov r9, 0
    mov r10, 0
    mov r11, rdi
    mov rdx, 0
    mov rcx, 0
    mov rax, 0
    mov rsi, 0

    mov rsi, 1

.l1:



    inc rcx
    cmp rcx, r11
    jnge .l1

    ret