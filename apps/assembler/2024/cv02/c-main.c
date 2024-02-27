#include <stdint.h>
#include <stdio.h>

long g_long_array[5] = {255, 594, 11, 45678, 321};
long g_counter = 0;
long g_output = 0;

char g_char_array[99] = "fsadfasdfasdfsdfsdauifu7fhhvdsfui IO cUIRINvOLuhfighafoadf";
char g_to_replace = 'f';
char g_new = 'K';

int g_ip_address = 0x0afe0a05;
int g_ip_mask = 0xffff0000;
uint8_t g_net_address[4] = {0, 0, 0, 0};

extern void even_sum();
extern size_t replace_chars();
extern void get_ip();

int main()
{
    even_sum();

    for (size_t i = 0; i < 5; i++)
    {
        printf("%ld\n", g_long_array[i]);
    }

    printf("%ld %ld\n\n\n", g_counter, g_output);

    printf("%s\n", g_char_array);
    size_t replaced_count = replace_chars();
    printf("%s, count of replaced chars %ld\n\n\n", g_char_array, replaced_count);

    get_ip();

    printf("%d.%d.%d.%d\n", g_net_address[0], g_net_address[1], g_net_address[2], g_net_address[3]);
}
