bits 64

section .data

    extern g_long_array, g_sum, g_remainder, g_count_of_bits
    extern g_char_replaced
    extern g_char_array, g_to_replace, g_new
    extern g_mac_address, g_vendor_oui, g_vendor_name

section .text

global g_sum_function
global g_replace
global g_mac_index

g_sum_function:
    mov rax, 0
    mov rdx, 0
    mov rdx, 5
    mov rcx, 0
    mov qword [g_sum], 0

.l1:
    add rax, [g_long_array + rcx * 8]

    cmp rcx, rdx
    inc rcx
    jnge .l1

    mov r9, 0
    mov r9, rax
    mov [g_sum], rax
    mov rdx, 0
    mov rdi, 0
    mov edi, 3

    IDIV edi

    mov rcx, 0
    mov rcx, 64

    mov r8, 0
    mov r8, r9

    mov rdi, 0
    mov [g_remainder], rdx
    cmp rdx, 0
    jne .l3
    
.l2:
    and r8, 0x1
    cmp r8, 1
    jne .l5
    
    inc rdi

.l5:
    shr r9, 1
    mov r8, r9
    loop .l2

    jmp .l6

.l3:
    and r8, 0x1
    cmp r8, 0
    jne .l4
    
    inc rdi

.l4:
    shr r9, 1
    mov r8, r9
    loop .l3

.l6:
    mov [g_count_of_bits], rdi

    ret 

g_replace:
    mov rax, 0
    mov rcx, 0
    mov rdx, 0
    mov rdi, 0
    mov rsi, 0

    mov dl, [g_to_replace]
    mov dil, [g_new]

.l1:
    mov al, [g_char_array + rcx]

    cmp al, dl
    jne .l2

    mov [g_char_array + rcx], dil
    inc rsi

.l2:

    inc rcx
    cmp al, 0
    jne .l1

    mov [g_char_replaced], rsi

    ret

g_mac_index:
    mov rax, 0
    mov rax, [g_mac_address]
    shr rax, 24
    
    mov rcx, -1
    mov rdx, 0
    mov rdx, 5

.l1: 
    inc rcx
    cmp eax, [g_vendor_oui + rcx * 4]
    je .l2

    cmp rcx, rdx
    jnge .l1

.l2:
    shl rax, 24
    mov [g_mac_address], rax

    mov rax, rcx

    ret