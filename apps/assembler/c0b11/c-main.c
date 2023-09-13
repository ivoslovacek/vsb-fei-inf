#include <stdio.h>

int isPalindrom(char *str);

/*
function gcd(a, b)
    while a ≠ b
        if a > b
            a := a − b
        else
            b := b − a
    return a
*/

int gcd(int *arr, int len);

void tribonacci(int n);

int main()
{
    char str[] = "okxko";

    int arr[] = {14, 24, 18, 25};

    printf("is %s palindrome %d\n", str, isPalindrom(str));

    printf("gcd is %d\n", gcd(arr, 4));

    return 0;
}
