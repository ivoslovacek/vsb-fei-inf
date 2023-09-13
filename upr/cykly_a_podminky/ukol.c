#include <stdio.h>

void first(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("x");
    }
    printf("\n\n");
}

void second(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("x\n");
    }
    printf("\n");
}

void third(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("x");
        }
        printf("\n");
    }
    printf("\n");
}

void fourth(int w, int h)
{
    int i, j;
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            printf("x");
        }
        printf("\n");
    }
    printf("\n");
}

void fifth(int n, int w)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < w; j++)
        {
            printf("x");
        }
        if (i + 1 == n)
        {
            printf("\n");
        }
        else
        {
            printf("\n\n");
        }
    }
    printf("\n");
}

void sixth(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                printf("x ");
            }
            else
            {
                printf("  ");
            }
        }
        if (i + 1 == n)
        {
            printf("\n");
        }
        else
        {
            printf("\n\n");
        }
    }
    printf("\n");
}

void seventh(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            printf(" ");
        }
        printf("x\n");
    }
    printf("\n");
}

void eight(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = n - (i + 1); j > 0; j--)
        {
            printf(" ");
        }
        printf("x\n");
    }
    printf("\n");
}

void ninth(int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 1; j < (n - i); j++)
        {
            printf(" ");
        }

        if (i == 0)
        {
            printf("x");
        }
        else if (i == n - 1)
        {
            for (j = 0; j < (2 * n - 1); j++)
            {
                printf("x");
            }
        }
        else
        {
            printf("x");
            for (j = n; j > (n - i); j--)
            {
                printf(" ");
            }
            if (i != 1)
            {
                for (j = n; j > (n - i + 1); j--)
                {
                    printf(" ");
                }
            }
            printf("x");
        }
        printf("\n");
    }
    printf("\n");
}

void tenth(int w, int h)
{
    char rectangle[w + 1][h];
    int i, j;
    char n = '0';

    for (i = 0; i < w; i++)
    {
        rectangle[i][0] = 'x';
        rectangle[i][h - 1] = 'x';
    }
    for (i = 0; i < h; i++)
    {
        rectangle[0][i] = 'x';

        rectangle[w - 1][i] = 'x';
    }

    for (i = 1; i < h - 1; i++)
    {
        for (j = 1; j < w - 1; j++)
        {
            rectangle[j][i] = n;
            if (n == '9')
            {
                n = '0';
            }
            else
                n++;
        }
    }

    for (i = 0; i < h; i++)
    {
        rectangle[w][i] = 10;
    }
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w + 1; j++)
        {
            printf("%c", rectangle[j][i]);
        }
    }
    printf("\n");
}

int main()
{
    int n, w, h;
    n = 4;
    w = 5;
    h = 6;

    scanf("%d %d %d", &n, &w, &h);

    first(n);
    second(n);
    third(n);
    fourth(w, h);
    fifth(n, w);
    sixth(n);
    seventh(n);
    eight(n);
    ninth(n);
    tenth(w, h);

    return 0;
}