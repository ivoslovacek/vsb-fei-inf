#include <stdio.h>

int g_int_array[15] = {-3, -8, 80, 2710, 32, 439, 9099, 10, 77, -273, 2, 22222, 0, -23, 23};
int g_int_output;
int g_neg_val_array[15];

char g_char_array[32] = "testovaci pole pro cv2";
int g_vowel_count;

void calculate_int_output();

void move_negatives();

void number_of_vowel();

void replace_vowels();

int main()
{
    calculate_int_output();

    printf("%d\n", g_int_output);

    move_negatives();

    for (int i = 0; i < 15; i++)
    {
        printf("%d, ", g_neg_val_array[i]);
    }
    printf("\n");

    number_of_vowel();

    printf("%d\n", g_vowel_count);

    replace_vowels();

    printf("%s", g_char_array);

    return 0;
}
