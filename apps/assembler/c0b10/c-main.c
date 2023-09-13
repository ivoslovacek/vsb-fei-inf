#include <stdio.h>
#include <stdlib.h>

void str_merge_diff(char *arr_in1, char *arr_in2, char *arr_out);

long arr_sum_and_return(long *arr1, int l_arr1, long *arr2, int l_arr2, int n);

int hamm_dist(int in1, int * arr1, int l_arr1);

int main()
{
    char *string1 = "ahoj ne";
    char *string2 = "ahoj ok";
    char *string3 = (char *)malloc(sizeof(char) * 100);

    str_merge_diff(string1, string2, string3);

    printf("%s\n", string3);

    long tmp[] = {4, 5, 6};
    long tmp2[] = {8, 2, 6, 15};
    int tmp3[] = {987,87,35,45};

    printf("%d\n", arr_sum_and_return(tmp, 3, tmp2, 4, 1));

    printf("%d", hamm_dist(456 , tmp3, 4));

    return 0;
}