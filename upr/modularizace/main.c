#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Wrong parameters");
        exit(EXIT_FAILURE);
    }

    Dictionary *dictionary = loadDictionary(argv[1]);

    FILE *input;
    input = fopen(argv[2], "r");
    if (input == NULL)
    {
        printf("Could not open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output;
    output = fopen(argv[3], "w");
    if (output == NULL)
    {
        printf("Could not open output file");
        exit(EXIT_FAILURE);
    }

    char *line = (char *)malloc(sizeof(char) * 256);

    for (int i = 0; !feof(input); i++)
    {
        fgets(line, 256, input);
        if (feof(input))
            break;

        for (int j = 0; line[j] != '\0'; j++)
        {
            if (line[j] == '\n')
            {
                line[j] = '\0';
            }
        }

        for (char *str = strtok(line, " "); str != NULL; str = strtok(NULL, " "))
        {

            fprintf(output, "%s ", translateWord(dictionary, str));
        }

        fprintf(output, "\n");
    }

    free(line);
    line = NULL;
    dictionary = freeDictionary(dictionary);
    fclose(input);
    fclose(output);
    return 0;
}