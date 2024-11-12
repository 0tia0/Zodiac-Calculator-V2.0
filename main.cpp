#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <map>
#include <string>

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 844
#define xCenter WINDOW_WIDTH / 2
#define yCenter WINDOW_HEIGHT / 2

#define WINDOW_TITLE "Zodiac Calculator V2.0"

#define wbDarkUnselected "./img/theme/wb/dark_unselected.jpg"
#define wbLightSelected "./img/theme/wb/light_selected.jpg"

#define bbDarkSelected "./img/theme/dark_selected.jpg"
#define bbLightUnselected "./img/theme/light_unselected.jpg"

#define textStep 20
#define defaultTextY 100

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

int themeSelection = 0; // 0 dark 1 light
int currentTextY = defaultTextY;

enum Keys
{
    LEFT_ARROW = 75,
    RIGHT_ARROW = 77,

    ENTER = 13
};

////////////////////
// TEXT FUNCTIONs //
//////////////////// 

int getCenteredX(char *title)
{
    int x = WINDOW_WIDTH - textwidth(title);
    return x / 2;
}

void updateTextY(char *title)
{
    currentTextY += textheight(title) + textStep;
}

void resetTextY()
{
    currentTextY = defaultTextY;
}

void printCenteredText(char *text, int FONT, int SIZE, bool updateY)
{
    settextstyle(FONT, HORIZ_DIR, SIZE);
    outtextxy(getCenteredX(text), currentTextY, text);
    if (updateY)
        updateTextY(text);
}

void leaveBlankSpace()
{
    currentTextY += defaultTextY;
}

////////////////////
//                //
////////////////////

void drawImage(int x, int y, int imgWidht, int imgHeight, char *path)
{
    int x1 = x - imgWidht / 2, x2 = x + imgWidht / 2, y1 = y - imgHeight / 2, y2 = y + imgHeight / 2;
    readimagefile(path, x1, y1, x2, y2);
}

void drawThemeMenu()
{
    switch (themeSelection)
    {
    case 0:
        setbkcolor(BLACK);
        cleardevice();

        setcolor(WHITE);
        printCenteredText("select theme", BOLD_FONT, 7, false);
        currentTextY += 70;
        printCenteredText("LEFT ARROW - RIGHT ARROW - ENTER", BOLD_FONT, 2, false);

        drawImage(xCenter + 250, yCenter, 200, 200, bbLightUnselected);
        drawImage(xCenter - 250, yCenter, 200, 200, bbDarkSelected);
        break;
    case 1:
        setbkcolor(WHITE);
        cleardevice();

        setcolor(BLACK);
        printCenteredText("select theme", BOLD_FONT, 7, false);
        currentTextY += 70;
        printCenteredText("LEFT ARROW - RIGHT ARROW - ENTER", BOLD_FONT, 2, false);

        drawImage(xCenter + 250, yCenter, 200, 200, wbLightSelected);
        drawImage(xCenter - 250, yCenter, 200, 200, wbDarkUnselected);
        break;
    default:
        break;
    }

    resetTextY();

}

void chooseTheme()
{
    bool done = false;
    int input = 0;

    while (!done)
    {
        drawThemeMenu();
        input = getch();
        switch (input)
        {
        case LEFT_ARROW:
            if (themeSelection == 1)
            {
                themeSelection = 0;
            }
            break;
        case RIGHT_ARROW:
            if (themeSelection == 0)
            {
                themeSelection = 1;
            }
            break;
        case ENTER:
            return;
            break;
        default:
            break;
        }
    }
}

int main()
{
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    setbkcolor(BLACK);
    cleardevice();

    chooseTheme();

    getch();
}