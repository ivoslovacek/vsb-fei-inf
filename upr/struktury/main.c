#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day;
    char name[101];
    float start;
    float end;
    float diff;
    int volume;
} akcie;

void checkArgs(int argc, char *argv[]);

int parseInput(char *input, int n, akcie *data, char *argv[]);

void parseAkcieToHtml(akcie *data, int n, char *argv[]);

void parseHighestToHtml(akcie *data, int i);

int main(int argc, char *argv[])
{
    checkArgs(argc, argv);

    int n = atoi(argv[2]);

    char *input = (char *)malloc(sizeof(char) * 101);
    akcie *data = (akcie *)malloc(sizeof(akcie) * n);
    int indexOfHighest = parseInput(input, n, data, argv);

    printf("<html>\n<body>\n<div>\n");
    parseHighestToHtml(data, indexOfHighest);
    printf("</div>\n<ul>\n");
    parseAkcieToHtml(data, n, argv);
    printf("</ul>\n</body>\n</html>\n");

    free(input);
    input = NULL;

    free(data);
    data = NULL;

    return 0;
}

void checkArgs(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }

    if (atoi(argv[2]) <= 0)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }
}

int parseInput(char *input, int n, akcie *data, char *argv[])
{
    int index;
    int indexOfHighest = -1;

    for (int i = 0; i < n; i++)
    {
        index = 0;

        fgets(input, 101, stdin);
        for (char *str = strtok(input, ","); str != NULL; str = strtok(NULL, ","))
        {
            switch (index)
            {
            case 0:
                data[i].day = atoi(str);
                break;
            case 1:
                strcpy(data[i].name, str);
                break;
            case 2:
                data[i].start = atof(str);
                break;
            case 3:
                data[i].end = atof(str);
                break;
            case 4:
                data[i].volume = atoi(str);
            }

            index++;
        }

        if (strcmp(data[i].name, argv[1]) == 0)
        {
            if (indexOfHighest == -1)
            {
                indexOfHighest = i;
            }
            else if (data[i].volume > data[indexOfHighest].volume)
            {
                indexOfHighest = i;
            }
        }

        data[i].diff = data[i].end - data[i].start;
    }

    return indexOfHighest;
}

void parseAkcieToHtml(akcie *data, int n, char *argv[])
{
    for (int i = (n - 1); i >= 0; i--)
    {
        if (strcmp(data[i].name, argv[1]) == 0)
        {
            printf("<li><b>Day: %d, ticker: %s, start: %.2f, end: %.2f, diff: %.2f, volume: %d</b></li>\n", data[i].day, data[i].name, data[i].start, data[i].end, data[i].diff, data[i].volume);
        }
        else
        {
            printf("<li>Day: %d, ticker: %s, start: %.2f, end: %.2f, diff: %.2f, volume: %d</li>\n", data[i].day, data[i].name, data[i].start, data[i].end, data[i].diff, data[i].volume);
        }
    }
}

void parseHighestToHtml(akcie *data, int i)
{
    if (i != -1)
    {
        printf("<h1>%s: highest volume</h1>\n", data[i].name);
        printf("<div>Day: %d</div>\n", data[i].day);
        printf("<div>Start price: %.2f</div>\n", data[i].start);
        printf("<div>End price: %.2f</div>\n", data[i].end);
        printf("<div>Volume: %d</div>\n", data[i].volume);
    }
    else
    {
        printf("Ticker AMC was not found\n");
    }
}