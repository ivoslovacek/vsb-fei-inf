#include <stdio.h>

int inputs(char *modei, int *counti, int *numbersi, int sizei)
{
    int tmp;
    char tmp2;
    scanf("%c", modei);
    if (*modei != 'h' && *modei != 'v')
    {
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    scanf("%d", counti);
    if (*counti < 0)
    {
        printf("neplatny pocet cisel");
        return 1;
    }

    for (int i = 0; i < *counti; i++)
    {
        scanf("%d%c", &tmp, &tmp2);
        if (tmp < 1 || tmp > 9)
            tmp = 1;

        if (tmp2 != ' ' && i != *counti - 1)
        {
            printf("cisla musi byt od sebe oddelena mezerou!");
            return 1;
        }

        ++*(numbersi + tmp - 1);
    }

    return 0;
}

void output(int *numberso, int sizeo, char *modeo)
{
    int height = *numberso;
    for (int i = 0; i < sizeo; i++)
    {
        if (height < *(numberso + i))
        {
            height = *(numberso + i);
        }
    }

    if (*modeo == 'v')
    {
        for (int i = 0; i < sizeo; i++)
        {
            printf("%d", i + 1);
            for (int j = 0; j < *(numberso + i); j++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
    else if (*modeo == 'h')
    {
        for (int i = height; i >= 0; i--)
        {
            for (int j = 0; j < sizeo; j++)
            {
                if (i == 0)
                {
                    printf("%d", j + 1);
                }
                else if (i <= *(numberso + j))
                {
                    printf("#");
                }
                else
                    printf(" ");
            }   

            printf("\n");
        }
    }
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    char mode = ' ';
    int count = 0;
    int numbers[9] = {0};

    if (inputs(&mode, &count, numbers, (sizeof(numbers) / sizeof(numbers[0]))))
        return 1;

    output(numbers, (sizeof(numbers) / sizeof(numbers[0])), &mode);

    return 0;
}