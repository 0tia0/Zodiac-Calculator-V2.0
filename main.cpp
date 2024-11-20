/*
    Zodiac Calculator V2.0                              This code can calculate your zodiac sign
                                                        cusp and ascendent basing on your born date.
    Code wrote by Mattia Marelli                        At the end of the execution it return also
    on 2024 as an homework for school                   an simple description of your sign
*/

#pragma region lib inclusion

////////////////////
// LIB INCLUSIONS //
////////////////////

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string.h>

#pragma end region

#pragma region definitions

/////////////////
// DEFINITIONS //
/////////////////

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 844
#define xCenter WINDOW_WIDTH / 2
#define yCenter WINDOW_HEIGHT / 2

#define WINDOW_TITLE "Zodiac Calculator V2.0"

#define wbDarkUnselected "./img/theme/wb/dark_unselected.jpg"
#define wbLightSelected "./img/theme/wb/light_selected.jpg"

#define bbDarkSelected "./img/theme/dark_selected.jpg"
#define bbLightUnselected "./img/theme/light_unselected.jpg"

#define intro "./img/background/intro.jpg"

#define textStep 20
#define defaultTextY 100

#pragma end region

#pragma region global variables

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

int themeSelection = 0; // 0 dark 1 light

int currentTextY = defaultTextY;

bool correct = false;      // is input stream correct
int input = 0;             // input
char inputStream[12] = ""; // input stream
int inputI = 0;            // input index

#pragma end region

#pragma region enums and arrays

//////////////////////
// ENUMS AND ARRAYS //
//////////////////////

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

const char *zodiacSignName[]{
    "CAPRICORNO",
    "ACQUARIO",
    "PESCI",
    "ARIETE",
    "TORO",
    "GEMELLI",
    "CANCRO",
    "LEONE",
    "VERGINE",
    "BILANCIA",
    "SCORPIONE",
    "SAGGITTARIO"};

const char *zodiacSignDescription[] = {
    "Il CAPRICORNO si associa a una persona ambiziosa e pragmatica, che punta sempre in alto.",
    "L'ACQUARIO si associa a una persona creativa e indipendente, che pensa fuori dagli schemi.",
    "I PESCI si associano a una persona empatica e sognatrice, che vive tra emozioni profonde.",
    "L'ARIETE si associa a una persona energica e coraggiosa, che affronta tutto con grinta.",
    "Il TORO si associa a una persona pragmatica e leale, un vero punto fermo per gli altri.",
    "I GEMELLI si associano a una persona curiosa e brillante, che ama esplorare nuove idee.",
    "Il CANCRO si associa a una persona sensibile e protettiva, che si dedica con amore.",
    "Il LEONE si associa a una persona carismatica e decisa, che brilla come il sole.",
    "La VERGINE si associa a una persona precisa e analitica, che eccelle nei dettagli.",
    "La BILANCIA si associa a una persona elegante e diplomatica, che cerca sempre l'armonia.",
    "Lo SCORPIONE si associa a una persona intensa e misteriosa, che affascina con il suo sguardo.",
    "Il SAGITTARIO si associa a una persona ottimista e avventurosa, che ama esplorare il mondo."};

#pragma end region

#pragma region structs

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

struct zodiacSign
{
    char name[50];
    char description[200];
    int sign;
    bool cusp;
    int ascendent;
};

#pragma end region

#pragma region text functions

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

#pragma end region

#pragma region image drawing

///////////////////
// IMAGE DRAWING //
///////////////////

void drawImage(int x, int y, int imgWidht, int imgHeight, char *path)
{
    int x1 = x - imgWidht / 2, x2 = x + imgWidht / 2, y1 = y - imgHeight / 2, y2 = y + imgHeight / 2;
    readimagefile(path, x1, y1, x2, y2);
}

#pragma end region

#pragma region menus

///////////
// MENUS //
///////////

/**
 * @brief this function draws on screen the theme selection menu updating the back color basing on selection
 */
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

/**
 * @brief display a simple spinning animation
 *
 * @param selectedImage based on sign calculation
 */
void animatedSign(int selectedImage)
{

    int i = 0;
    int j = 0;
    char *files[] = {
        "./img/sign/sign_1.jpg",
        "./img/sign/sign_2.jpg",
        "./img/sign/sign_3.jpg",
        "./img/sign/sign_4.jpg",
        "./img/sign/sign_5.jpg",
        "./img/sign/sign_6.jpg",
        "./img/sign/sign_7.jpg",
        "./img/sign/sign_8.jpg",
        "./img/sign/sign_9.jpg",
        "./img/sign/sign_10.jpg",
        "./img/sign/sign_11.jpg",
        "./img/sign/sign_12.jpg",
    };

    readimagefile("./img/sign/sign_0.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (j = 0; j < 100; j += 10)
    {
        if (selectedImage < 12)
        {
            for (int i = selectedImage; i <= 12; i++)
            {
                readimagefile(files[i - 1], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                delay(j);
            }
        }

        // Secondo ciclo: conta da 1 a 12
        for (int i = 1; i <= selectedImage; i++)
        {
            readimagefile(files[i - 1], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
            delay(j);
        }
    }

    for (i = 0; i < 5; i++)
    {
        readimagefile("./img/sign/sign_0.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        delay(50);
        readimagefile(files[selectedImage - 1], 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        delay(100);
    }
}

#pragma end region

#pragma region data elaboration functions

////////////////////////////////
// DATA ELABORATION FUNCTIONs //
////////////////////////////////

/**
 * @brief check if the year in the struct d is bisestile
 *
 * @param d the date to check
 * @return true if bisestile
 * @return false is !bisestile
 */
bool checkBisestile(birthDate d)
{
    // bisestile se divisibile per 4 ma non per 100 a meno che non lo sia anche per 400
    if ((d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief check if the date exist
 *
 * @param d the date to check
 * @return true if exist
 * @return false is !exist
 */
bool dateExist(birthDate d)
{

    // giorni in ogni mese
    int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // controllo mese
    if (d.month < 1 || d.month > 12)
    {
        return false;
    }

    // controllo specifico per febbraio bisestile
    if (d.month == 2 && checkBisestile(d))
    {
        dayInMonth[1] = 29;
    }

    // controllo giorno
    if (d.day < 1 || d.day > dayInMonth[d.month - 1])
    {
        return false;
    }

    return true;
}

/**
 * @brief convert the date to the days passed since the start of the year, for example if you born on 10/02 we can say that you're born on the 41fs day of the year
 *
 * @param d the date to convert
 * @param isBisestile is the year bisestile?
 * @return int the total of the days
 */
int fromDateToDays(birthDate d, bool isBisestile)
{

    int totalDays = 0;
    // giorni passatti da 1 gennaio al mese scelto, giorni totali uguale a day + uno dei valori
    int daysGone[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    // calcolo giorni
    if (d.month == 1)
    {
        totalDays = d.day;
    }
    else
    {
        totalDays = daysGone[d.month - 1] + d.day;
    }

    // aggiunti di un giorno se la data e dopo febbraio in un anno bisestile perche febbraio != 28 ma = 29
    if (d.month > 2 && isBisestile)
    {
        totalDays++;
    }

    return totalDays;
}

/**
 * @brief format the input string in day, month and year
 *
 * @param dataStream input string
 * @param d struct where to save the date
 */
void formatDate(const char *dataStream, birthDate *d)
{
    sscanf(dataStream, "%2d/%2d/%4d", &d->day, &d->month, &d->year);
}

/**
 * @brief check if the time exist
 *
 * @param t the time to check
 * @return true if exist
 * @return false is !exist
 */
bool timeExist(birthTime t)
{

    if (t.hour < 0 || t.hour > 24)
        return false;
    if (t.minute < 0 || t.minute > 60)
        return false;
    if (t.hour == 24 && t.minute > 0)
        return false;

    return true;
}

/**
 * @brief format the input string in hour and minute
 *
 * @param dataStream input string
 * @param t struct where to save the time
 */
void formatTime(const char *dataStream, birthTime *t)
{
    sscanf(dataStream, "%2d:%2d", &t->hour, &t->minute);
}

#pragma end region

#pragma region sign calculation, cusp and ascendent

//////////////////////////////////////////
// SIGN CALCULATION, CUSP AND ASCENDENT //
//////////////////////////////////////////

/**
 * @brief calculate the sign basing on the date
 *
 * @param d the date from the user
 * @param cusp the variable to save if is cusp
 * @return int corrisponding to the sign
 */
int getSign(birthDate d, bool *cusp)
{
    bool isBisestile = checkBisestile(d);
    int totalDays = fromDateToDays(d, isBisestile);
    int sign = 0;

    int signRange[2][2][13] = {
        {
            // NORMALE
            {1, 20, 50, 80, 110, 140, 171, 202, 233, 263, 293, 322, 356},  // start
            {19, 49, 79, 109, 139, 170, 201, 232, 262, 292, 321, 355, 365} // end
        },
        {
            // BISESTILE
            {1, 20, 51, 81, 111, 141, 172, 203, 234, 264, 294, 323, 357},  // start
            {19, 50, 80, 110, 140, 171, 202, 233, 263, 293, 322, 356, 366} // end
        }};

    for (int i = 0; i < 13; i++)
    {
        if (totalDays >= signRange[isBisestile][0][i] && totalDays <= signRange[isBisestile][1][i])
        {
            // Controllo cuspide
            if (totalDays == signRange[isBisestile][0][i] || totalDays == signRange[isBisestile][1][i])
            {
                *cusp = true;
            }

            // Determinazione del segno
            sign = (i == 12) ? 1 : i + 1;
            break;
        }
    }

    return sign;
}

/**
 * @brief calculate the ascendent basing on the date
 *
 * @param d the date from the user
 * @return int corrisponding to the ascendent
 */
int getAscendent(birthDate d)
{
    const double romeLat = 41.9028;
    const double romeLong = 12.4964;

    double decimalHour = d.time.hour + d.time.minute / 60.0;
    double localHour = decimalHour + (romeLong / 15.0);

    while (localHour < 0)
        localHour += 24;
    while (localHour >= 24)
        localHour -= 24;

    int ascendent = static_cast<int>(localHour / 2);
    ascendent = (ascendent % 12) + 1;

    ascendent += 3;
    if (ascendent > 12)
    {
        ascendent -= 12;
    }

    return ascendent;
}

/**
 * @brief fill the zodiacSign struct with all the stuffs
 *
 * @param d the date inserted
 * @param t the time inserted
 * @return zodiacSign struct
 */
zodiacSign calculateSign(birthDate d, birthTime t)
{
    zodiacSign zS = {0};
    d.time = t;

    zS.sign = getSign(d, &zS.cusp);

    strcpy(zS.name, zodiacSignName[zS.sign - 1]);
    strcpy(zS.description, zodiacSignDescription[zS.sign - 1]);

    zS.ascendent = getAscendent(d);

    return zS;
}

#pragma end region

#pragma region input from screen

////////////////////////////////
// GET TEXT INPUT FROM SCREEN //
////////////////////////////////

/**
 * @brief delete a char after a backspace in screen input window
 */
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

/**
 * @brief check if the inserted input is correct
 *
 * @param text the input string
 * @param type the type of date (M_DATE or M_TIME)
 * @param data the raw data to be converted in data or time struct
 * @return true if is valid
 * @return false if is invalid
 */
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
        formatDate(text, date);
        return dateExist(*date);
    case M_TIME:
        formatTime(text, time);
        return timeExist(*time);
    default:
        break;
    }
}

/**
 * @brief automatically ad a seprator if needed
 *
 * @param type time or date to choose between / and :
 * @return true / false
 */
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

/**
 * @brief Get input from the screen, check if it is correct and save it
 *
 * @param type of the data inserted
 * @param data where the data should be inserted
 */
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

        // ignore ctrl
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

#pragma end region

#pragma region asking to user

//////////////////////////////
// ASKING TO USER SOMETHING //
//////////////////////////////

/**
 * @brief ask user to choose a theme
 */
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

/**
 * @brief ask for a date and save it
 *
 * @return birthDate to save the data
 */
birthDate chooseBirthDate()
{
    birthDate date;
    askForInput("Inserire la propria data di nascita", "(dd/mm/yyyy)");
    getInput(M_DATE, &date);
    leaveBlankSpace();
    return date;
}

/**
 * @brief ask for time and save it
 *
 * @return birthTime to save the data
 */
birthTime chooseBirtTime()
{
    birthTime time;
    askForInput("Inserire la propria ora di nascita", "(hh/mm)");
    getInput(M_TIME, &time);
    leaveBlankSpace();
    return time;
}

#pragma end region

#pragma region main

//////////
// MAIN //
//////////

int main()
{
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    setbkcolor(BLACK);
    cleardevice();

    // INTRO SCREEN
    drawImage(xCenter, yCenter, WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, intro);
    delay(3000);

    // CHOOSE SCREEN THEME
    chooseTheme();

    // READ FROM SCREEN
    currentTextY += 150;
    birthDate date = chooseBirthDate();
    birthTime time = chooseBirtTime();

    // ZODIAC SIGN CALCULATION CUSP AND ASCENDENT
    zodiacSign sign = calculateSign(date, time);

    cleardevice();

    animatedSign(sign.sign);
    delay(2000);
    cleardevice();

    resetTextY();
    leaveBlankSpace();

    printCenteredText("il tuo segno zodiacale e\':", BOLD_FONT, 4, false);
    currentTextY += 50;
    if (sign.cusp)
    {
        strcat(sign.name, " - sei una cuspide");
        printCenteredText(sign.name, BOLD_FONT, 3, true);
    }
    else
    {
        printCenteredText(sign.name, BOLD_FONT, 3, true);
    }

    leaveBlankSpace();

    printCenteredText("il tuo segno ascendnete e\':", BOLD_FONT, 4, false);
    currentTextY += 50;
    char *ascendentName;
    strcpy(ascendentName, zodiacSignName[sign.ascendent]);
    printCenteredText(ascendentName, BOLD_FONT, 3, true);

    leaveBlankSpace();
    printCenteredText(sign.description, BOLD_FONT, 3, true);

    delay(20000);
}