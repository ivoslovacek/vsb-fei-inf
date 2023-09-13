#include <stdio.h>
#include <stdlib.h>

long intPow(int x, int y);
int stringToInt(char *strings);
char *createNstrings(int n);
int getNumber();
int getLines(char *strings, int n);
char *linesToWords(char *strings, int n, int wordCount);
char *changeCapitalLetters(char *words, int wordCount);
int countOfUpperLetters(char *word);
int countOfLowerLetters(char *word);
char *toUpper(char *words, int wordCount);
char *toLower(char *words, int wordCount);
int isPalindrome(char *word);
void setmem(char *arr, int c, int size);

int main()
{
    int n = getNumber();
    char *strings = createNstrings(n);
    int wordCount = getLines(strings, n);
    char *words = linesToWords(strings, n, wordCount + 1);

    free(strings);
    strings = NULL;

    char *words2 = changeCapitalLetters(words, wordCount + 1);
    char *words3 = toLower(words, wordCount + 1);
    char *words4 = toUpper(words, wordCount + 1);

    for (int i = 0; i <= wordCount; i++)
    {
        printf("Slovo %d: ", i);
        printf("%s ", (words + (i * 100)));
        printf("%s ", (words2 + (i * 100)));
        printf("%d ", countOfLowerLetters(words + (i * 100)));
        printf("%d ", countOfUpperLetters(words + (i * 100)));
        printf("%s ", (words3 + (i * 100)));
        printf("%s ", (words4 + (i * 100)));
        printf("%d ", isPalindrome(words + (i * 100)));
        printf("\n");
    }

    free(words);
    words = NULL;
    free(words2);
    words2 = NULL;
    free(words3);
    words3 = NULL;
    free(words4);
    words4 = NULL;

    return 0;
}

long intPow(int x, int y)
{
    long tmp = 1;
    for (int i = 0; i < y; i++)
    {
        tmp = tmp * x;
    }

    return tmp;
}

int stringToInt(char *strings)
{
    int tmp = 0;
    int index = 0;
    int currentPos = -1;

    for (int i = 0; strings[i] != '\0'; i++)
    {
        if (strings[i] >= '0' && strings[i] <= '9')
            currentPos++;
    }

    for (int i = currentPos; i >= 0; i--)
    {
        tmp = tmp + (strings[i] - 48) * intPow(10, index);
        index++;
    }

    return tmp;
}

int getNumber()
{
    int n;
    char *tmp = (char *)malloc(sizeof(char) * 5);
    if (tmp == NULL)
    {
        printf("couldnt allocate memory");
        exit(EXIT_FAILURE);
    }

    if (fgets(tmp, sizeof(char) * 5, stdin) == NULL)
    {
        printf("failed input");
        exit(EXIT_FAILURE);
    }

    n = stringToInt(tmp);

    free(tmp);
    tmp = NULL;

    return n;
}

char *createNstrings(int n)
{
    char *ptr = (char *)malloc(sizeof(char) * n * 101);
    if (ptr == NULL)
    {
        printf("couldnt allocate memory");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

int getLines(char *strings, int n)
{
    int wordCount = -1;
    for (int i = 0; i < n; i++)
    {
        if (fgets((strings + i * 101), 101, stdin) == NULL)
        {
            printf("failed input");
            exit(EXIT_FAILURE);
        }

        for (int j = (i * 101); strings[j] != '\0'; j++)
        {
            if ((strings[j] < 'A' || (strings[j] > 'Z' && strings[j] < 'a') || strings[j] > 'z') && strings[j] != '\n' && strings[j] != ' ')
            {
                printf("words can only contain letters of the alphabet");
                exit(EXIT_FAILURE);
            }
            else if (strings[j] == ' ' || strings[j + 1] == '\0')
            {
                wordCount++;
            }
        }
    }

    return wordCount;
}

char *linesToWords(char *strings, int n, int wordCount)
{
    int tmp = 0;
    int currentWord = 0;

    char *ptr = (char *)malloc(sizeof(char) * wordCount * 100);
    setmem(ptr, 0, (wordCount * 100));

    for (int i = 0; i < n; i++)
    {
        for (int j = (i * 101); strings[j] != '\0' * 101; j++)
        {
            if (strings[j] != ' ' && strings[j] != '\n' && strings[j + 1] != '\0')
            {
                ptr[(currentWord * 100) + tmp] = strings[j];
                tmp++;
            }
            else
            {
                if (strings[j + 1] == 0)
                {
                    ptr[(currentWord * 100) + tmp + 1] = '\0';
                }
                else
                {
                    ptr[(currentWord * 100) + tmp] = '\0';
                }

                currentWord++;
                tmp = 0;
            }
        }
    }

    return ptr;
}

char *changeCapitalLetters(char *words, int wordCount)
{
    char *words2 = (char *)malloc(sizeof(char) * 100 * wordCount);
    setmem(words2, 0, (wordCount * 100));

    for (int i = 0; i < wordCount; i++)
    {
        for (int j = (i * 100); words[j] != '\0'; j++)
        {
            if (words[j] >= 'A' && words[j] <= 'Z')
            {
                words2[j] = words[j] + 32;
            }
            else
            {
                words2[j] = words[j] - 32;
            }
        }
    }

    return words2;
}

int countOfUpperLetters(char *word)
{
    int tmp = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            tmp++;
        }
    }

    return tmp;
}

int countOfLowerLetters(char *word)
{
    int tmp = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            tmp++;
        }
    }

    return tmp;
}

char *toUpper(char *words, int wordCount)
{
    char *words2 = (char *)malloc(sizeof(char) * 100 * wordCount);
    setmem(words2, 0, (wordCount * 100));

    for (int i = 0; i < wordCount; i++)
    {
        for (int j = (i * 100); words[j] != '\0'; j++)
        {
            if (words[j] >= 'a' && words[j] <= 'z')
            {
                words2[j] = words[j] - 32;
            }
            else
            {
                words2[j] = words[j];
            }

            if (words[j + 1] == '\0')
            {
                words2[j + 1] == '\0';
            }
        }
    }

    return words2;
}

char *toLower(char *words, int wordCount)
{
    char *words2 = (char *)malloc(sizeof(char) * 100 * wordCount);
    setmem(words2, 0, (wordCount * 100));

    for (int i = 0; i < wordCount; i++)
    {
        for (int j = (i * 100); words[j] != '\0'; j++)
        {
            if (words[j] >= 'A' && words[j] <= 'Z')
            {
                words2[j] = words[j] + 32;
            }
            else
            {
                words2[j] = words[j];
            }

            if (words[j + 1] == '\0')
            {
                words2[j + 1] == '\0';
            }
        }
    }

    return words2;
}

int isPalindrome(char *word)
{
    int tmp = -1;

    for (int i = 0; word[i] != '\0'; i++)
    {
        tmp++;
    }

    for (int i = 0; i <= tmp; i++)
    {
        if (word[i] == word[tmp])
        {
            if (tmp == i)
            {
                return 1;
            }
            tmp--;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

void setmem(char *arr, int c, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = c;
    }
}