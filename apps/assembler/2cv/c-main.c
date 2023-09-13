#include <stdio.h>

long g_long_array[5] = { 1153, 76, 52, 44211, 582362};
long g_sum, g_count_of_bits, g_remainder;

char g_char_array[99] = "asfhsdufgauifu7fhhvuhfighafoadf";
char g_to_replace = 'f';
char g_new = 'x';
int g_char_replaced;
  
long g_mac_address = 0x309c2323ab65;
int g_vendor_oui[5] = {4120,3185699,14448460,3199042};
char g_vendor_name[5] = {'B','M','C','D','A'};

void g_sum_function();

void g_replace();

int g_mac_index();

int main()
{
    g_sum_function();
    printf("%ld %ld %ld\n", g_sum, g_remainder, g_count_of_bits);

    g_replace();
    printf("%s %d\n", g_char_array, g_char_replaced);

    printf("%lx %c", g_mac_address, g_vendor_name[g_mac_index()]);

    return 0;
}
    