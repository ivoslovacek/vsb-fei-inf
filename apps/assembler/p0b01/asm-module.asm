    bits 64

    section .data

extern g_int_array
extern g_char_array
extern g_int_output
extern g_neg_val_array
extern g_vowel_count

    section .text

global calculate_int_output
global move_negatives
global number_of_vowel
global replace_vowels

calculate_int_output:
    ; clear registers
    mov rax, 0 ; this register will be used for finding if the number is even
    mov rcx, 0 ; loop counter
    mov rdx, 0 ; count of even numbers

    ; loop setup
    mov rcx, 15 ; move the size of the array into loop counter

l1:
    dec rcx ; decrement counter
    
    mov eax, [g_int_array + rcx * 4] ; move a number from array indicated by value stored in "rcx"
    and eax, 1 ; use a mask to only keep LSB
    cmp eax, 1 ; check if LSB is 1
    jnz l2 ; if LSB wasnt 1, the number in "eax" is even and we jump to label l2

l3:
    cmp rcx, 0 ; check "rcx" with 0
    jnle l1 ; if the number in "rcx" isnt smaller then 0 we jump to l1

    and edx, 0x11 ; we use a mask to get only the 2 LSB bits, which would be the remainder of dividing by 4
    not edx ; negate the number in register "edx"
    mov [g_int_output], edx ; move the number in register "edx" to variable g_int_output

    ret


l2:
    inc edx ; increment our count of numbers
    jmp l3 ; jump to label l3

move_negatives:
    ; clear registers
    mov rax, 0 ; this register will be used for finding if the number is negative
    mov rcx, 0 ; loop counter
    mov rdx, 0 ; used to indicate the current index in the negative array

    ; loop setup
    mov rcx, 15 ; move the size of the array into loop counter

l4:
    dec rcx ; decrement counter
    
    mov eax, [g_int_array + rcx * 4] ; move a number from array indicated by value stored in "rcx"
    cmp eax, 0 ; compare the number with 0
    jl l5 ; if the number is smaller then 0, jump to l5
l6:
    cmp rcx, 0 ; check "rcx" with 0
    jnle l4 ; if the number in "rcx" isnt smaller then 0 we jump to l4

    ret

l5:
    mov [g_neg_val_array + rdx * 4], eax ; move the number from "eax" into the array on index indicated by "rdx"
    inc rdx ; increment our negative array index
    jmp l6 ; jump to label l6

number_of_vowel:
    ; clear registers
    mov rax, 0 ; register for storing the current char
    mov rcx, 0 ; loop counter
    mov rdx, 0 ; g_vowel_count

l7:
    mov al, [g_char_array + rcx] ; move a character from array with index "rcx" to register "al"

    ; compare character stored in "al" to vowels if the char is a vowel, jump to l9
    cmp al, 'a'
    jz l9

    cmp al, 'e'
    jz l9
    
    cmp al, 'i'
    jz l9

    cmp al, 'o'
    jz l9

    cmp al, 'u'
    jz l9

    cmp al, 'y'
    jz l9

l8:
    inc rcx ; increment loop counter
    cmp al, 0 ; check if we are at the end of the string
    jnz l7 ; if the numbers are not equal, jump to l7

    mov [g_vowel_count], edx ; move the number of vowels in "rdx" to variable g_g_vowel_count

    ret

l9:
    inc rdx ; increase our g_vowel_count
    jmp l8 ; jump to l8


replace_vowels:
    ; clear registers
    mov rax, 0 ; register for storing the current char
    mov rcx, 0 ; loop counter
    mov rdx, 0 ; relative count of vowels

l10:
    mov al, [g_char_array + rcx] ; move a character from array with index "rcx" to register "al"

    ; compare character stored in "al" to vowels if the char is a vowel, jump to l9
    cmp al, 'a'
    jz l11

    cmp al, 'e'
    jz l11
    
    cmp al, 'i'
    jz l11

    cmp al, 'o'
    jz l11

    cmp al, 'u'
    jz l11

    cmp al, 'y'
    jz l11

l12:
    inc rcx ; increment loop counter
    cmp al, 0 ; check if we are at the end of the string
    jnz l10 ; if the numbers are not equal, jump to l7

    ret

l11:
    cmp rdx, 2 ; check if we are at the third vowel
    jz l13 ; if so we jump to label l13

l14:
    inc rdx ; increment our relative counter of vowels
    mov rsi, 0 ; set register "rsi" to 0
    cmp rdx, 3 ; check if number on register "rdx" is 3
    cmove rdx, rsi ; if it is move the value of register "rsi" (the 0 we set) to register  "rdx", this resets our relative count of vowels

    jmp l12 ; jump to label l12

l13:
    mov byte [g_char_array + rcx], '3' ; replace the current char in array indexed by "rcx" by char '3'

    jmp l14 ; jump to label l14