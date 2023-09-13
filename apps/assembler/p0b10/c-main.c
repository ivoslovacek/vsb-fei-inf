#include <stdio.h>
#include <stdlib.h>

void str_cp_part(char *to, char *from, long start, long stop);

int str_count_numbers(char * in);

long rect_perimeter(int a, int b);

int main()
{
    char g_string[64] = "kryplkara je nejlepsi";

    char *string;
    string = (char *)malloc(sizeof(char) * 64);

    str_cp_part(string, g_string, 0, 9);

    int count = str_count_numbers(g_string);

    long obvod = rect_perimeter(5, 10);

    printf("original: %s\ncopied: %s\n%d\n%ld\n", g_string, string, count, obvod);

    free(string);

    return 0;
}