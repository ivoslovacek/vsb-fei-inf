#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

// Height of each character.
const int FONT_ROW_HEIGHT = 34;

typedef unsigned char byte;

typedef struct
{
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct
{
    byte b;
    byte g;
    byte r;
} RGBPixel;

typedef struct
{
    TGAHeader header;
    RGBPixel *pixels;
    int width;
    int height;
} Image;

// Loads an image from the given `path`.
// If loading fails, return false.
bool image_load(Image *image, const char *path)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        return false;
    }

    memset(image, 0, sizeof(Image));
    fread(&image->header, sizeof(image->header), 1, file);

    // We only support RGB images.
    assert(image->header.depth == 24);
    assert(image->header.image_type == 2);

    memcpy(&image->width, &image->header.width, sizeof(image->header.width));
    memcpy(&image->height, &image->header.height, sizeof(image->header.height));

    image->pixels = (RGBPixel *)malloc(sizeof(RGBPixel) * image->width * image->height);
    fread(image->pixels, sizeof(RGBPixel) * image->width * image->height, 1, file);

    fclose(file);

    return true;
}

// Free the memory of the given image.
void image_free(Image *image)
{
    free(image->pixels);
}

Image *image_loadfont(Image *fonts, const char *path, size_t count);

void image_freefonts(Image *fonts, size_t size);

void free_strings(char **str, size_t size);

bool image_writeimage(Image *image, const char *path);

int string_pixelwidth(char *str, Image *fonts);

bool image_writestringtoimage(Image *image, Image *fonts, char **str1, size_t size1, char **str2, size_t size2);

bool string_checkvalidityandconvert(char *str);

void image_writechar(Image *image, Image *fonts, char a, int x, int y);

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Wrong parameters");
        return 1;
    }

    Image src;
    if (!image_load(&src, argv[1]))
    {
        printf("Could not load image");
        return 1;
    }

    Image *fonts = image_loadfont(fonts, argv[3], 26);

    char *parameters = (char *)malloc(sizeof(char) * 101);
    if (parameters == NULL)
    {
        printf("Couldnt allocate memory");
        return 1;
    }
    fgets(parameters, 101, stdin);

    for (int i = 0; parameters[i]; i++)
    {
        if (parameters[i] == '\n' || parameters[i] == ' ')
            parameters[i] = '\0';
    }

    int top = atoi(parameters);
    int bottom = atoi((parameters + strlen(parameters) + 1));
    free(parameters);

    char **topStrings;
    char **bottomStrings;

    if (top > 0)
    {
        topStrings = (char **)malloc(sizeof(char *) * top);
        if (topStrings == NULL)
        {
            printf("Couldnt allocate memory");
        }
        for (int i = 0; i < top; i++)
        {
            if (topStrings[i] == NULL)
            {
                printf("Couldnt allocate memory");
            }
            topStrings[i] = (char *)malloc(sizeof(char) * 101);
            fgets(topStrings[i], 101, stdin);
            if (!string_checkvalidityandconvert(topStrings[i]))
            {
                printf("invalid text");
                free_strings(topStrings, top);
                image_freefonts(fonts, 26);
                image_free(&src);
                return 1;
            }
        }
    }

    if (bottom > 0)
    {
        bottomStrings = (char **)malloc(sizeof(char *) * bottom);
        if (bottomStrings == NULL)
        {
            printf("Couldnt allocate memory");
        }
        for (int i = 0; i < bottom; i++)
        {

            if (bottomStrings[i] == NULL)
            {
                printf("Couldnt allocate memory");
            }
            bottomStrings[i] = (char *)malloc(sizeof(char) * 101);
            fgets(bottomStrings[i], 101, stdin);
            if (!string_checkvalidityandconvert(bottomStrings[i]))
            {
                printf("invalid text");
                free_strings(topStrings, top);
                free_strings(bottomStrings, bottom);
                image_freefonts(fonts, 26);
                image_free(&src);
                return 1;
            }
        }
    }

    if (!image_writestringtoimage(&src, fonts, topStrings, top, bottomStrings, bottom))
    {
        printf("couldnt allocate memory");
    }

    if (!image_writeimage(&src, argv[2]))
    {
        free_strings(topStrings, top);
        free_strings(bottomStrings, bottom);
        image_freefonts(fonts, 26);
        image_free(&src);
        return 1;
    }

    free_strings(topStrings, top);
    free_strings(bottomStrings, bottom);
    image_freefonts(fonts, 26);
    image_free(&src);
    return 0;
}

Image *image_loadfont(Image *fonts, const char *path, size_t count)
{
    fonts = (Image *)malloc(sizeof(Image) * count);
    if (fonts == NULL)
    {
        printf("Couldn't allocate memory");
        exit(1);
    }

    char *pathToLetter = (char *)malloc(sizeof(char) * (strlen(path) + 8));
    if (pathToLetter == NULL)
    {
        printf("Couldn't allocate memory");
        exit(1);
    }
    strcpy(pathToLetter, path);
    strncat((pathToLetter + strlen(path)), "/A.tga ", 6);

    for (int i = 0; i < count; i++)
    {
        if (!image_load((fonts + i), pathToLetter))
        {
            printf("Couldnt open font");
            exit(1);
        }
        pathToLetter[strlen(path) + 1]++;
    }

    free(pathToLetter);
    return fonts;
}

void image_freefonts(Image *fonts, size_t count)
{
    for (int i = 0; i < count; i++)
    {
        image_free((fonts + i));
    }
    free(fonts);
}

void free_strings(char **str, size_t size)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            free(str[i]);
        }

        free(str);
    }
}

bool image_writeimage(Image *image, const char *path)
{
    FILE *file = fopen(path, "wb");
    if (file == NULL)
    {
        printf("Could create a new image!");
        return false;
    }

    fwrite(&image->header, sizeof(image->header), 1, file);
    fwrite(image->pixels, sizeof(RGBPixel) * image->width * image->height, 1, file);

    fclose(file);
    return true;
}

bool image_writestringtoimage(Image *image, Image *fonts, char **str1, size_t size1, char **str2, size_t size2)
{
    int *str1x = (int *)malloc(sizeof(int) * size1);
    int *str2x = (int *)malloc(sizeof(int) * size2);

    if (str1x == NULL || str2x == NULL)
    {
        return false;
    }

    int currentx;
    int currenty = 0;

    for (int i = 0; i < size1; i++)
    {
        str1x[i] = (image->width / 2) - (string_pixelwidth(str1[i], fonts) / 2);
    }

    for (int i = 0; i < size2; i++)
    {
        str2x[i] = (image->width / 2) - (string_pixelwidth(str2[i], fonts) / 2);
    }

    for (int i = 0; i < size1; i++)
    {
        currentx = str1x[i];
        for (int j = 0; str1[i][j] != '\0'; j++)
        {
            if (str1[i][j] != ' ')
            {
                image_writechar(image, fonts, str1[i][j], currentx, currenty);
                currentx += fonts[str1[i][j] - 65].width;
            }
            else
            {
                currentx += 12;
            }
        }
        currenty += 34;
    }

    currenty = image->height - 45;

    for (int i = size2 - 1; i >= 0; i--)
    {
        currentx = str2x[i];
        for (int j = 0; str2[i][j] != '\0'; j++)
        {
            if (str2[i][j] != ' ')
            {
                image_writechar(image, fonts, str2[i][j], currentx, currenty);
                currentx += fonts[str2[i][j] - 65].width;
            }
            else
            {
                currentx += 12;
            }
        }
        currenty -= 34;
    }

    free(str1x);
    free(str2x);
    str1x = NULL;
    str2x = NULL;

    return true;
}

int string_pixelwidth(char *str, Image *fonts)
{
    int tmp = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
        {
            tmp += fonts[str[i] - 65].width;
        }
        else
        {
            tmp += 20;
        }
    }

    return tmp;
}

bool string_checkvalidityandconvert(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < 'A' || str[i] > 'Z')
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] -= 32;
            }
            else
            {
                if (str[i] == ' ')
                {
                }
                else if (str[i] == '\n')
                {
                    str[i] = '\0';
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void image_writechar(Image *image, Image *fonts, char a, int startx, int starty)
{
    for (int x = 0; x < fonts[a - 65].width; x++)
    {
        for (int y = 0; y < fonts[a - 65].height; y++)
        {
            if (fonts[a - 65].pixels[x + fonts[a - 65].width * y].r != 0 && fonts[a - 65].pixels[x + fonts[a - 65].width * y].r != 0 && fonts[a - 65].pixels[x + fonts[a - 65].width * y].r != 0)
            {
                image->pixels[startx + x + image->width * (starty + y)].r = fonts[a - 65].pixels[x + fonts[a - 65].width * y].r;
                image->pixels[startx + x + image->width * (starty + y)].g = fonts[a - 65].pixels[x + fonts[a - 65].width * y].g;
                image->pixels[startx + x + image->width * (starty + y)].b = fonts[a - 65].pixels[x + fonts[a - 65].width * y].b;
            }
        }
    }
}