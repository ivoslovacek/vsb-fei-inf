#pragma once
#include <stdio.h>

typedef struct
{
    char **dict;
    int lines;
} Dictionary;

Dictionary *loadDictionary(char *dict_path);

Dictionary *freeDictionary(Dictionary *dict);

char *translateWord(Dictionary *dict, char *word);