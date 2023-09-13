#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

char *allocateLine()
{
    char *ptr = (char *)malloc(sizeof(char) * 256);

    return ptr;
}

Dictionary *loadDictionary(char *dict_path)
{
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));

    FILE *dict_csv;
    dict_csv = fopen(dict_path, "r");
    if (dict_csv == NULL)
    {
        printf("Could not load dictionary");
        exit(EXIT_FAILURE);
    }

    dict->dict = (char **)malloc(sizeof(char *) * 1);

    int i;
    fseek(dict_csv, 0, SEEK_SET);

    for (i = 0; !feof(dict_csv); i++)
    {
        dict->dict = realloc(dict->dict, sizeof(char *) * (i + 1));
        if (dict->dict == NULL)
        {
            printf("reallocation of memory failed!");
            exit(EXIT_FAILURE);
        }
        dict->dict[i] = allocateLine();

        fgets(dict->dict[i], 256, dict_csv);
        if (feof(dict_csv))
            break;
        for (int j = 0; dict->dict[i][j] != '\0'; j++)
        {
            if (dict->dict[i][j] == '\n' || dict->dict[i][j] == ',')
            {
                dict->dict[i][j] = '\0';
            }
        }
    }
    dict->lines = i + 1;

    fclose(dict_csv);

    return dict;
}

char *translateWord(Dictionary *dict, char *word)
{
    for (int i = 0; i < dict->lines; i++)
    {
        if (strcmp(dict->dict[i], word) == 0)
        {
            return dict->dict[i] + strlen(dict->dict[i]) + 1;
        }
    }

    return "<unknown>";
}

Dictionary *freeDictionary(Dictionary *dict)
{
    for (int i = 0; i < dict->lines; i++)
    {
        free(dict->dict[i]);
    }
    free(dict->dict);
    free(dict);

    return NULL;
}