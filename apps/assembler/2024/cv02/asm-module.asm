bits 64

section .data

extern g_long_array
extern g_counter
extern g_output

extern g_char_array
extern g_to_replace
extern g_new

extern g_ip_address
extern g_ip_mask
extern g_net_address

section .text

global even_sum
even_sum:
; setup stack frame
    push rbp
    mov rbp, rsp
    sub rsp, 16

; zero out each used register
    xor rcx, rcx
    xor rdx, rdx
    xor rdi, rdi

; store the length of the array in rdi
    mov rdi, 5

; beginning of a loop
l1:
; check if the end of the array was reached
    cmp rcx, rdi
    jge l2

; move g_long_array[rcx] to rdx
    xor rdx, rdx
    mov rdx, qword [g_long_array + rcx * 8]
    not rdx
    mov qword [g_long_array + rcx * 8], rdx

; increment rcx and jump
    inc rcx 
    jmp l1
l2:

; store the array len onto the stack
    mov qword [rbp - 8], rcx

; setup rcx as loop counter
    xor rcx, rcx
; move the array size into rdi
    mov rdi, [rbp - 8]

; beginning of a loop
l3:  
; check if the end of the array was reached
    cmp rcx, rdi
    jge l4

; move g_long_array[rcx] to rdx
    xor rdx, rdx
    mov rdx, qword [g_long_array + rcx * 8]

; copy the value from rdx to rax
    mov rax, rdx

; check if the number is even
    and rax, 1
    cmp rax, 0
    jne not_even

; if even then add it to our total count stored on stack
; at [rbp - 16]
    add qword[rbp - 16], rdx

not_even:
; increment rcx and jmp
    inc rcx
    jmp l3
l4:

; move our sum of even numbers to rax
    xor rax, rax
    mov rax, qword [rbp - 16]

; move 5 into rcx
    xor rcx, rcx
    mov rcx, 5

; clear rdx for the idiv instruction as it divides rdx:rax
    xor rdx, rdx

; check if rax is a negative integer
    cmp rax, 0
    jnl no_sign

; if so, sign extend rax into rdx
    not rdx

no_sign:

; divide value in rax by the value in rcx
; (REX.W indicates that its a 64bit operation)
    REX.W idiv rcx

; move the divided sum from rax to g_output
    mov qword [g_output], rax

; move the size of the array to g_counter
    xor rax, rax
    mov rax, [rbp - 8]
    mov qword [g_counter], rax

; restore stack
    mov rsp, rbp
    pop rbp
    ret

global replace_chars
replace_chars:
; setup stack frame
    push rbp
    mov rbp, rsp
   
; setup rcx and rdi for use in the loop
    xor rcx, rcx
    xor rdi, rdi
; setup rax for counting the chars replaced

loop:
; load the current char into dl
    mov dl, [g_char_array + rcx]

; check if the end of the string was reached ('\0')
    cmp dl, 0
    je end_loop

; check if the current char should be replaced
    cmp dl, [g_to_replace]
    jne not_replaced

; if so, replace the char
    mov dl, [g_new]
    mov byte [g_char_array + rcx], dl

; increment our counter in rax
    inc rax

not_replaced:
   
    inc rcx
    jmp loop
end_loop:

; restore stack
    mov rsp, rbp
    pop rbp

; returning from the function will also return the value from rax
; as the return value of the function
    ret

global get_ip
get_ip:
; setup stack frame
    push rbp
    mov rbp, rsp

; move ip address to rax and apply mask
    xor rax, rax
    mov rax, qword [g_ip_address]
    and rax, qword [g_ip_mask]

; setup loop
    xor rcx, 3

; setup mask for moving values into the ip array
    xor rdx, rdx
    mov rdx, 0xff

loop2:
; check if the last byte of the ip was written 
    cmp rcx, 0
    jl end_loop2

; mask the full ip with our new mask
    xor rsi, rsi
    mov rsi, rax
    and rsi, rdx

; adjust the full ip address for the next iteration by bit shifting
    shr rax, 8

; move the new ip slice into the ip array
    mov byte [g_net_address + rcx], sil

; decrement rcx and jump
    dec rcx
    jmp loop2

end_loop2:

; restore stack
    mov rsp, rbp
    pop rbp
    ret

