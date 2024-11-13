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

bool correct = false;
int input = 0;
char inputStream[12] = "";
int inputI = 0;

///////////
// ENUMS //
///////////

enum Keys
{
    LEFT_ARROW = 75,
    RIGHT_ARROW = 77,

    ENTER = 13
};

enum dataType
{
    M_DATE,
    M_TIME
};

/////////////
// STRUCTs //
/////////////

typedef struct
{
    int hour;
    int minute;
} birthTime;

typedef struct
{
    int day;
    int month;
    int year;

    birthTime time;
} birthDate;

////////////////////
// TEXT FUNCTIONs //
////////////////////

/**
 * @brief get the centered x to place the text
 *
 * @param title text to center
 * @return the position where to place the text
 */
int getCenteredX(char *title)
{
    int x = WINDOW_WIDTH - textwidth(title);
    return x / 2;
}

/**
 * @brief update the y index by a default step
 *
 * @param title the last text printed to the screen
 */
void updateTextY(char *title)
{
    currentTextY += textheight(title) + textStep;
}

/**
 * @brief reset the y index to the default value
 */
void resetTextY()
{
    currentTextY = defaultTextY;
}

/**
 * @brief automaticcaly place a text centered in the correct y
 *
 * @param text the text to print
 * @param FONT the font to use
 * @param SIZE the size of the text
 * @param updateY chose if update or not the y index, so if the next text should be on the same line or not
 */
void printCenteredText(char *text, int FONT, int SIZE, bool updateY)
{
    settextstyle(FONT, HORIZ_DIR, SIZE);
    outtextxy(getCenteredX(text), currentTextY, text);
    if (updateY)
        updateTextY(text);
}

/**
 * @brief print to screen the question for the user
 *
 * @param question question for the user like: How old are you?
 * @param format the expect format of the data
 */
void askForInput(char *question, char *format)
{
    printCenteredText(question, BOLD_FONT, 4, false);
    currentTextY += 35;
    printCenteredText(format, BOLD_FONT, 3, true);
}

/**
 * @brief leave a blank line
 */
void leaveBlankSpace()
{
    currentTextY += defaultTextY;
}

///////////////////
// IMAGE DRAWING //
///////////////////

void drawImage(int x, int y, int imgWidht, int imgHeight, char *path)
{
    int x1 = x - imgWidht / 2, x2 = x + imgWidht / 2, y1 = y - imgHeight / 2, y2 = y + imgHeight / 2;
    readimagefile(path, x1, y1, x2, y2);
}

///////////
// MENUS //
///////////

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

////////////////////////////////
// DATA ELABORATION FUNCTIONs //
////////////////////////////////

bool checkBisestile(int y)
{
    // bisestile se divisibile per 4 ma non per 100 a meno che non lo sia anche per 400
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool dateExist(int d, int m, int y)
{

    // giorni in ogni mese
    int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // controllo mese
    if (m < 1 || m > 12)
    {
        return false;
    }

    // controllo specifico per febbraio bisestile
    if (m == 2 && checkBisestile(y))
    {
        dayInMonth[1] = 29;
    }

    // controllo giorno
    if (d < 1 || d > dayInMonth[m - 1])
    {
        return false;
    }

    return true;
}

int fromDateToDays(int day, int month, bool isBisestile)
{

    int totalDays = 0;
    // giorni passatti da 1 gennaio al mese scelto, giorni totali uguale a day + uno dei valori
    int daysGone[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    // calcolo giorni
    if (month == 1)
    {
        totalDays = day;
    }
    else
    {
        totalDays = daysGone[month - 1] + day;
    }

    // aggiunti di un giorno se la data e dopo febbraio in un anno bisestile perche febbraio != 28 ma = 29
    if (month > 2 && isBisestile)
    {
        totalDays++;
    }

    return totalDays;
}

void formatDate(const char *dataStream, int *d, int *m, int *y)
{

    sscanf(dataStream, "%2d/%2d/%4d", d, m, y);

    // fix 05 -> 5
    if (*d < 10)
    {
        *d = *d % 10;
    }
    if (*m < 10)
    {
        *m = *m % 10;
    }
}

bool timeExist(int h, int m)
{

    if (h < 0 || h > 24)
        return false;
    if (m < 0 || m > 60)
        return false;

    return true;
}

void formatTime(const char *dataStream, int *h, int *m)
{

    sscanf(dataStream, "%2d:%2d", h, m);

    // fix 05 -> 5
    if (*h < 10)
    {
        *h = *h % 10;
    }
    if (*m < 10)
    {
        *m = *m % 10;
    }
}

////////////////////////////////
// GET TEXT INPUT FROM SCREEN //
////////////////////////////////

void deleteChar()
{
    setcolor(0);
    printCenteredText(inputStream, COMPLEX_FONT, 4, false);
    inputStream[inputI - 1] = ' ';
    inputI--;
    if (themeSelection)
    {
        setcolor(DARKGRAY);
    }
    else
    {
        setcolor(LIGHTGRAY);
    }
    printCenteredText(inputStream, COMPLEX_FONT, 4, false);
}

bool checkInput(char *text, int type, void *data)
{
    birthDate *date = nullptr;
    birthTime *time = nullptr;

    if (type)
    {
        time = (birthTime *)data;
    }
    else
    {
        date = (birthDate *)data;
    }

    switch (type)
    {
    case M_DATE:
        formatDate(text, &date->day, &date->month, &date->year);
        return dateExist(date->day, date->month, date->year);
    case M_TIME:
        formatTime(text, &time->hour, &time->minute);
        return timeExist(time->hour, time->minute);
    default:
        break;
    }
}

bool addSeparator(int type)
{
    switch (type)
    {
    case M_DATE:
        if (inputI == 2 || inputI == 5)
        {
            inputStream[inputI] = '/';
            printCenteredText(inputStream, COMPLEX_FONT, 4, false);
            inputI++;
            return true;
        }
    case M_TIME:
        if (inputI == 2)
        {
            inputStream[inputI] = ':';
            printCenteredText(inputStream, COMPLEX_FONT, 4, false);
            inputI++;
            return true;
        }
    default:
        break;
    }

    return false;
}

void getInput(int type, void *data)
{
    if (themeSelection)
    {
        setcolor(DARKGRAY);
    }
    else
    {
        setcolor(LIGHTGRAY);
    }

    input = 0;
    for (int i = 0; i < 12; ++i)
    {
        inputStream[i] = '\0';
    }
    inputI = 0;
    correct = false;

    while (!correct)
    {
        input = getch();

        // ignore ctlr
        if (input == 127)
            continue;

        // delete function
        if (input == 8 && inputI > 0)
        {
            deleteChar();
            continue;
        }

        // controllo inserimento numeri
        else if (input >= 48 && input <= 57 && (type == M_DATE && inputI < 10 || type == M_TIME && inputI < 5))
        {
            inputStream[inputI] = input;
            printCenteredText(inputStream, COMPLEX_FONT, 4, false);
            inputI++;
        }

        // inserimento automatico parentesi
        if (addSeparator(type))
            continue;

        // check data completa e pressione invio eseguo formattazione data + check correttezza
        if (type == M_DATE && inputI == 10 || type == M_TIME && inputI == 5)
        {
            if (input == 13)
            {
                correct = checkInput(inputStream, type, data);
                if (!correct)
                {
                    setcolor(0);
                    printCenteredText(inputStream, COMPLEX_FONT, 4, false);
                    setcolor(RED);
                    printCenteredText(inputStream, COMPLEX_FONT, 4, false);
                    char *error = "Dati inseriti non validi, Riprova!";
                    showerrorbox(error);
                }
                else
                {
                    setcolor(0);
                    printCenteredText(inputStream, COMPLEX_FONT, 4, false);
                    setcolor(GREEN);
                    printCenteredText(inputStream, COMPLEX_FONT, 4, false);
                    if (themeSelection)
                    {
                        setcolor(BLACK);
                    }
                    else
                    {
                        setcolor(WHITE);
                    }
                    return;
                }
            }
        }
    }
}

//////////////////////////////
// ASKING TO USER SOMETHING //
//////////////////////////////

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
            cleardevice();
            return;
            break;
        default:
            break;
        }
    }
}

birthDate chooseBirthDate()
{
    birthDate date;
    askForInput("Inserire la propria data di nascita", "(dd/mm/yyyy)");
    getInput(M_DATE, &date);
    leaveBlankSpace();
    return date;
}

birthTime chooseBirtTime()
{
    birthTime time;
    askForInput("Inserire la propria ora di nascita", "(hh/mm)");
    getInput(M_TIME, &time);
    leaveBlankSpace();
    return time;
}

//////////
// MAIN //
//////////

int main()
{
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    setbkcolor(BLACK);
    cleardevice();

    chooseTheme();

    currentTextY += 150;
    chooseBirthDate();
    chooseBirtTime();

    getch();
}