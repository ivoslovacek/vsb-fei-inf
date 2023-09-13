#include <stdio.h>
#include <stdlib.h>

int gridsize(int *rows, int *cols)
{
    scanf("%d %d", rows, cols);

    return 0;
}

void setarraytodot(char *arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(arr + i * cols + j) = '.';
        }
    }
}

int movement(char *grid, int rows, int cols, int *posx, int *posy)
{
    char tmp;

    scanf("%c", &tmp);

    switch (tmp)
    {
    case 'o':
        *(grid + cols * (*posy) + (*posx)) = 'o';
        break;
    case '<':
        if (*posx == 0)
        {
            *posx = (cols - 1);
        }
        else
        {
            (*posx)--;
        }
        break;
    case '>':
        if (*posx == (cols - 1))
        {
            *posx = 0;
        }
        else
        {
            (*posx)++;
        }
        break;
    case '^':
        if (*posy == 0)
        {
            *posy = (rows - 1);
        }
        else
        {
            (*posy)--;
        }
        break;
    case 'v':
        if (*posy == (rows - 1))
        {
            *posy = 0;
        }
        else
        {
            (*posy)++;
        }
        break;
    case 'x':
        return 0;
    default:
        break;
    }

    return 1;
}

void loop(char *grid, int rows, int cols, int *posx, int *posy)
{
    while (movement(grid, rows, cols, posx, posy));
}

void draw(char *grid, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", *(grid + i * cols + j));
        }
        printf("\n");
    }
}

int main()
{

    int rows, cols;
    int posx = 0;
    int posy = 0;
    char *grid = NULL;

    if (gridsize(&rows, &cols))
        return 1;

    grid = (char *)malloc(sizeof(char) * rows * cols);

    if (grid == NULL)
    {
        printf("memory allocation failed");
        return 1;
    }

    setarraytodot(grid, rows, cols);

    loop(grid, rows, cols, &posx, &posy);

    draw(grid, rows, cols);

    free(grid);
    return 0;
}