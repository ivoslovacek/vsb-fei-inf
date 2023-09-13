//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Functions
// void some_asm_function();

// Variables
// type g_some_c_variable;

void decode();

int enc_string;
char decoded[4];

void extend_and_merge();
int first_extended;
int last_extended;
long merged;

int main()
{

    enc_string = 0x50415053;
    decode();
    printf("String = %s\n", decoded);

    extend_and_merge();
    printf("Result merged=%#010lx\n", merged);

    return 0;
}
    