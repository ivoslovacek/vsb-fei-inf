#include <stdio.h>
#include <unistd.h>

// ANSI escape sequences reference:
// - https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#cursor-navigation
// - https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html

// Height of the drawing canvas
int canvas_height = 40;

//---Cursor management---

// Hide the blinking terminal cursor.
void hide_cursor();

// Show the terminal cursor.
void show_cursor();

//---Color management---

// Reset the drawing and background color to the default values.
void reset_color();

// Set the background color to red.
void set_red_color();

// Set the background color to green.
void set_green_color();

// Set the background color to blue.
void set_blue_color();

//---Screen management---

// Reset the drawing environment.
// Clears the screen, moves the cursor to the origin in the top-left corner and
// prepares the drawing canvas.
void clear_screen();

//---Cursor movement---

// Move cursor right.
void move_right();

// Move cursor left.
void move_left();

// Move cursor up.
void move_up();

// Move cursor down.
void move_down();

// Move cursor to the specified `line` and `column` position.
void move_to(int line, int column);

//---Drawing---

// Draws a single "pixel" using the currently set background color.
// The cursor position is not changed after drawing!
// You need to move the cursor manually before drawing the next pixel,
// otherwise you will just overwrite the previous pixel.
void draw_pixel();

// Clears the drawing session, resets colors and cursor.
// Call this before the end of the program, otherwise your terminal will get messed up.
void end_drawing();

// Pause the program for a while, so that you can see what has been drawn so far.
// If you repeatedly call animate() after drawing something, you can crate interactive animations.
// You can also combine this with clear_screen() to draw something new on every "animation frame".
void animate();

void vesnice(int n);

void dum(int w, int corx, int cory);

void cara(int n);

void schody(int n);

void animace();
//----------------------------
// Put your functions here

int negative(int u);

int main()
{
    int s, u;

    do
    {
        clear_screen();
        move_to(1, 1);
        show_cursor();
        printf("vyberte co vykreslit pomoci zadani cisla:\n");
        printf("1. vykresleni domu\n");
        printf("2. vykresleni vesnice\n");
        printf("3. vykresleni prerusovane cary\n");
        printf("4. vykresleni schodu\n");
        printf("5. animace schodiste\n");

        scanf("%d", &s);
    } while (s <= 0 || s > 5);

    switch (s)
    {
    case 1:
        clear_screen();
        move_to(1, 1);
        show_cursor();

        printf("zadejte sirku domu: ");

        scanf("%d", &u);
        if (negative(u))
            return 1;

        clear_screen();
        move_to(1, 1);
        set_blue_color();

        dum(u, 1, 1);

        break;

    case 2:
        clear_screen();
        move_to(1, 1);
        show_cursor();

        printf("zadejte pocet domu: ");

        scanf("%d", &u);
        if (negative(u))
            return 1;

        vesnice(u);

        break;

    case 3:
        clear_screen();
        move_to(1, 1);
        show_cursor();

        printf("zadejte delku cary: ");

        scanf("%d", &u);
        if (negative(u))
            return 1;

        cara(u);

        break;

    case 4:
        clear_screen();
        move_to(1, 1);
        show_cursor();

        printf("zadejte pocet shodu: ");

        scanf("%d", &u);
        if (negative(u))
            return 1;

        schody(u);

        break;

    case 5:
        clear_screen();
        move_to(1, 1);
        show_cursor();

        printf("zadejte pocet schodu, ktere budou animovany: ");

        scanf("%d", &u);
        if (negative(u))
            return 1;

        animace(u);

        break;

    default:
        return 1;
    }

    // Keep this line here
    end_drawing();

    return 0;
}

int negative(int u)
{
    if (u <= 0)
    {
        printf("zadana hodnota nemuze byt 0 nebo zaporna!");
        return 1;
    }
    else
        return 0;
}

//----------------------------

void dum(int w, int corx, int cory)
{
    int a, x, h, is_even;

    if (w % 2)
    {
        x = (w + 1) / 2;
        is_even = 0;
    }
    else
    {
        x = w / 2;
        is_even = 1;
    }

    h = w + x;

    int dum[h][w];

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            dum[i][j] = 0;
        }
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == h - 1 || i == x || (j == 0 && i >= x) || (j == w - 1 && i >= x))
            {
                dum[i][j] = 1;
            }
        }
    }

    if (is_even)
    {
        a = x - 1;
        for (int i = 0; i < w; i++)
        {
            if (i < x - 1)
            {
                dum[a][i] = 1;
                a--;
            }
            else if (i == x - 1)
            {
                dum[a][i] = 1;
            }
            else if (i >= x)
            {
                dum[a][i] = 1;
                a++;
            }
        }
    }
    else
    {
        a = x - 1;
        for (int i = 0; i < w; i++)
        {
            if (i < x - 1)
            {
                dum[a][i] = 1;
                a--;
            }
            else if (i == x - 1)
            {
                dum[a][i] = 1;
                a++;
            }
            else if (i >= x)
            {
                dum[a][i] = 1;
                a++;
            }
        }
    }

    for (int i = cory; i < cory + h; i++)
    {
        for (int j = corx; j < corx + w; j++)
        {
            if (dum[i - cory][j - corx] == 1)
            {
                move_to(i, j);
                draw_pixel();
            }
        }
    }
}

void vesnice(int n)
{
    int width[n];
    int corx = 1;
    int cory = 1;
    int max_height = 0;
    int h;

    clear_screen();
    move_to(1, 1);
    show_cursor();

    for (int i = 0; i < n; i++)
    {
        printf("zadejte sirku domku cislo %d: ", i + 1);
        scanf("%d", &width[i]);
        if (negative(width[i]))
            return;
    }

    clear_screen();
    move_to(1, 1);
    set_blue_color();

    for (int i = 0; i < n; i++)
    {
        dum(width[i], corx, cory);

        if (width[i] % 2)
        {
            h = width[i] + ((width[i] + 1) / 2);
        }
        else
        {
            h = width[i] + width[i] / 2;
        }

        if (h > max_height)
            max_height = h;

        corx = corx + width[i] + 1;

        if (i != n - 1 && corx + width[i] + 1 >= 40)
        {
            corx = 1;
            cory = cory + max_height + 1;
        }
    }
}

void cara(int n)
{
    clear_screen();
    move_to(1, 1);
    set_blue_color();

    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        move_right();
        move_right();
    }
}

void schody(int n)
{
    clear_screen();
    move_to(1, 1);
    set_blue_color();

    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        move_right();
        draw_pixel();
        move_right();
        draw_pixel();
        move_down();
    }
}

void animace(int n)
{
    clear_screen();
    move_to(1, 1);
    set_blue_color();

    for (int i = 0; i < n; i++)
    {
        draw_pixel();
        move_right();
        draw_pixel();
        move_right();
        draw_pixel();
        move_down();
        animate();
    }
}

void hide_cursor()
{
    printf("\x1b[?25l");
}
void show_cursor()
{
    printf("\x1b[?25h");
}

void reset_color()
{
    printf("\x1b[0m");
}
void set_red_color()
{
    printf("\x1b[41;1m");
}
void set_green_color()
{
    printf("\x1b[42;1m");
}
void set_blue_color()
{
    printf("\x1b[44;1m");
}

void clear_screen()
{
    reset_color();
    hide_cursor();

    // Clear screen
    printf("\x1b[2J");
    // Move cursor to (0, 0)
    printf("\x1b[0;0F");
    // Create canvas
    for (int i = 0; i < canvas_height; i++)
    {
        printf("\n");
    }
    for (int i = 0; i < canvas_height; i++)
    {
        printf("\x1b[1A");
    }
}

void move_right()
{
    printf("\x1b[1C");
}
void move_left()
{
    printf("\x1b[1D");
}
void move_up()
{
    printf("\x1b[1A");
}
void move_down()
{
    printf("\x1b[1B");
}
void move_to(int line, int column)
{
    printf("\x1b[%d;%dH", line, column);
}

void draw_pixel()
{
    printf(" ");
    move_left();
}
void end_drawing()
{
    reset_color();
    printf("\x1b[0;0H");
    for (int i = 0; i < canvas_height; i++)
    {
        move_down();
    }
    printf("\n");
    show_cursor();
}
void animate()
{
    fflush(stdout);
    // Sleep for 500ms
    usleep(1000 * 500);
}