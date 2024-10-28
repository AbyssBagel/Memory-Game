#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAXROW 10 // MAX NUMBER OF ROWS
#define MAXCOL 10 // MAX NUMBER OF COLUMNS
#define MINROW 2  // MIN NUMBER OF ROWS
#define MINCOL 2  // MAX NUMBER OF COLUMNS

#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3
#define PURPLE 4
#define CYAN 5
#define WHITE 6
#define BLACK 7

#define T 5

void Color(int couleurDuTexte, int couleurDeFond);
/// Function to initialize the grid, the array is an input/output, nrow and ncol as well,
/// minrow, maxrow, mincol and maxcol are input
int InitGame(char *TabMemory, int *TabEtat, int *prow, int *pcol, int minrow, int maxrow, int mincol, int maxcol);
void PrintMemory(const char *Tab, int row, int col);
void PrintMemoryZoom(const char *Tab, int row, int col);
void swapchar(char *C1, char *C2);
int shuffle(char *Tab, int row, int col);
void PrintMemoryConditionned(const char *TabMemory, const int *TabEtat, int row, int col);
void PrintMemoryConditionnedZoom(const char *TabMemory, const int *TabEtat, int row, int col);
int GetChoice(int *pi, int *pj, const int *tab, int n, int m);
void PrintWelcomeScreen(void);
void myfflush(void);
void Pause(void);
int mygets(char *pS, int cap);

int main(void)
{
    PrintWelcomeScreen();
    int i1, j1, i2, j2, row, col, TabEtat[52];
    char TabMemory[52], a, b;
    srand(time(NULL));
    int nbredecoup = 0, nbredecoupmax, FoundPair = 0;
    InitGame(TabMemory, TabEtat, &row, &col, MINROW, MAXROW, MINCOL, MAXCOL);
    shuffle(TabMemory, row, col);
    PrintMemoryZoom(TabMemory, row, col);
    Sleep(T * 1000);
    const int nbredepair = (row * col) / 2;
    nbredecoupmax = row * col;
    do
    {
        PrintMemoryConditionnedZoom(TabMemory, TabEtat, row, col);
        nbredecoup++;
        printf("\nSelect a first case (format row/column : 00) : ");
        GetChoice(&i1, &j1, TabEtat, row, col);
        if (TabEtat[i1 * col + j1] == 0)
        {
            TabEtat[i1 * col + j1] = 1;
            PrintMemoryConditionnedZoom(TabMemory, TabEtat, row, col);
            printf("\nSelect a second case (format row/column : 00) : ");
            GetChoice(&i2, &j2, TabEtat, row, col);
            if (TabEtat[i2 * col + j2] == 0)
            {
                TabEtat[i2 * col + j2] = 1;
                PrintMemoryConditionnedZoom(TabMemory, TabEtat, row, col);
                Sleep(1000);
                if (TabMemory[i1 * col + j1] != TabMemory[i2 * col + j2])
                {
                    TabEtat[i1 * col + j1] = 0;
                    TabEtat[i2 * col + j2] = 0;
                }
                else
                {
                    FoundPair++;
                }
            }
            else
            {
                TabEtat[i1 * col + j1] = 0;
            }
        }
    } while (nbredecoup < nbredecoupmax && FoundPair != nbredepair);
    PrintMemoryZoom(TabMemory, row, col);
    if (FoundPair == nbredepair)
    {
        printf("\nCongratulations you may have the best memory in the entire universe ! ");
    }
    else
    {
        printf("\nSorry, you lost, you'll have to train your memory !");
    }
}

int InitGame(char *TabMemory, int *TabEtat, int *prow, int *pcol, int minrow, int maxrow, int mincol, int maxcol)
{
    int i, j;
    do
    {
        printf("How many rows do you want to play with ? ");
        scanf("%d", prow);
        myfflush();

        if (*prow < minrow || *prow > maxrow)
        {
            printf("Error: Number of rows must be between %d and %d.\n", minrow, maxrow);
            Pause();
        }
        system("cls");
    } while (*prow < minrow || *prow > maxrow);

    do
    {
        printf("How many columns do you want to play with ? ");
        scanf("%d", pcol);
        myfflush();

        if (*pcol < mincol || *pcol > min(maxcol, 52 / (*prow)) || *pcol % 2 != 0)
        {
            printf("Error: Number of columns must be between %d and %d (even), and compatible with the number of rows.\n", mincol, min(maxcol, 52 / (*prow)));
            Pause();
        }
        system("cls");
    } while ((*pcol < mincol || *pcol > min(maxcol, 52 / (*prow))) || (*pcol % 2 != 0));

    for (i = 0; i < *prow; i++)
    {
        for (j = 0; j < *pcol; j++)
        {
            TabEtat[i * (*pcol) + j] = 0;
            TabMemory[i * (*pcol) + j] = 65 + ((*pcol) * i + j) / 2;
        }
    }
}

void PrintMemory(const char *Tab, int row, int col)
{
    int i, j;
    system("cls");
    Color(WHITE, BLACK);
    printf(" ");
    for (i = 0; i < col; i++)
    {
        printf("%d", i);
    }
    printf("\n");
    for (i = 0; i < row; i++)
    {
        printf("%d", i);
        for (j = 0; j < col; j++)
        {
            if (Tab[i * col + j] > 'A' && Tab[i * col + j] < 'G')
            {
                Color(Tab[i * col + j] % 66 + 1, BLACK);
            }
            if (Tab[i * col + j] > 'G' && Tab[i * col + j] < 'M')
            {
                Color(Tab[i * col + j] % 72 + 1, BLACK);
            }
            if (Tab[i * col + j] > 'M' && Tab[i * col + j] < 'S')
            {
                Color(Tab[i * col + j] % 78 + 1, BLACK);
            }
            if (Tab[i * col + j] > 'S' && Tab[i * col + j] < 'Y')
            {
                Color(Tab[i * col + j] % 84 + 1, BLACK);
            }
            if (Tab[i * col + j] == 'A' || Tab[i * col + j] == 'G' || Tab[i * col + j] == 'M' || Tab[i * col + j] == 'S' || Tab[i * col + j] == 'Y')
            {
                Color(0, BLACK);
            }
            printf("%c", Tab[i * col + j]);
            Color(WHITE, BLACK);
        }
        printf("\n");
    }
}

void swapchar(char *C1, char *C2)
{
    char change;
    change = *C1;
    *C1 = *C2;
    *C2 = change;
}

int shuffle(char *Tab, int row, int col)
{
    int i, j, i2, j2;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            i2 = rand() % row;
            j2 = rand() % col;
            swapchar(&Tab[i * col + j], &Tab[i2 * col + j2]);
        }
    }
}

void PrintMemoryConditionned(const char *TabMemory, const int *TabEtat, int row, int col)
{
    int i, j;
    system("cls");
    Color(WHITE, BLACK);
    printf(" ");
    for (i = 0; i < col; i++)
    {
        printf("%d", i);
    }
    printf("\n");
    for (i = 0; i < row; i++)
    {
        printf("%d", i);
        for (j = 0; j < col; j++)
        {
            if (TabEtat[i * col + j] == 1)
            {
                if (TabMemory[i * col + j] > 'A' && TabMemory[i * col + j] < 'G')
                {
                    Color(TabEtat[i * col + j] % 66 + 1, BLACK);
                }
                if (TabMemory[i * col + j] > 'G' && TabMemory[i * col + j] < 'M')
                {
                    Color(TabMemory[i * col + j] % 72 + 1, BLACK);
                }
                if (TabMemory[i * col + j] > 'M' && TabMemory[i * col + j] < 'S')
                {
                    Color(TabMemory[i * col + j] % 78 + 1, BLACK);
                }
                if (TabMemory[i * col + j] > 'S' && TabMemory[i * col + j] < 'Y')
                {
                    Color(TabMemory[i * col + j] % 84 + 1, BLACK);
                }
                if (TabMemory[i * col + j] == 'A' || TabMemory[i * col + j] == 'G' || TabMemory[i * col + j] == 'M' || TabMemory[i * col + j] == 'S' || TabMemory[i * col + j] == 'Y')
                {
                    Color(0, BLACK);
                }
                printf("%c", TabMemory[i * col + j]);
                Color(WHITE, BLACK);
            }
            else
            {
                printf("?");
            }
        }
        printf("\n");
    }
}

int GetChoice(int *pi, int *pj, const int *tab, int n, int m)
{
    char Choice[3];
    Choice[0] = '\0';
    do
    {
        mygets(Choice, 3);

        if (Choice[0] < '0' || Choice[0] > '0' + n || Choice[1] < '0' || Choice[1] >= '0' + m)
        {
            printf("Error, please enter a correct format : \n");
        }
    } while (Choice[0] < '0' || Choice[0] > '0' + n || Choice[1] < '0' || Choice[1] >= '0' + m);
    *pi = Choice[0] - '0';
    *pj = Choice[1] - '0';
    if (tab[*pi * m + *pj] == 1)
    {
        printf("Play carefully, this case is already visible, you lost one run \n");
        Pause();
        return 1;
    }
    return 0;
}

void PrintMemoryZoom(const char *Tab, int row, int col)
{
    int i, j, k, SizeCaseRow = 3;
    system("cls");
    Color(WHITE, BLACK);
    printf("    ");
    for (i = 0; i < col; i++)
    {
        printf("%4d", i);
    }
    printf("\n");
    for (i = 0; i < row; i++)
    {
        for (k = 0; k < SizeCaseRow; k++)
        {
            if (k == SizeCaseRow / 2)
            {
                printf("%4d", i);

                for (j = 0; j < col; j++)
                {
                    if (Tab[i * col + j] > 'A' && Tab[i * col + j] < 'G')
                    {
                        Color(Tab[i * col + j] % 66 + 1, BLACK);
                    }
                    if (Tab[i * col + j] > 'G' && Tab[i * col + j] < 'M')
                    {
                        Color(Tab[i * col + j] % 72 + 1, BLACK);
                    }
                    if (Tab[i * col + j] > 'M' && Tab[i * col + j] < 'S')
                    {
                        Color(Tab[i * col + j] % 78 + 1, BLACK);
                    }
                    if (Tab[i * col + j] > 'S' && Tab[i * col + j] < 'Y')
                    {
                        Color(Tab[i * col + j] % 84 + 1, BLACK);
                    }
                    if (Tab[i * col + j] == 'A' || Tab[i * col + j] == 'G' || Tab[i * col + j] == 'M' || Tab[i * col + j] == 'S' || Tab[i * col + j] == 'Y')
                    {
                        Color(0, BLACK);
                    }
                    printf("%4c", Tab[i * col + j]);
                    Color(WHITE, BLACK);
                }
            }
            else
            {
                printf("\n");
            }
        }
    }
}

void PrintMemoryConditionnedZoom(const char *TabMemory, const int *TabEtat, int row, int col)
{
    int i, j, k, SizeCaseRow = 3;
    system("cls");
    Color(WHITE, BLACK);
    printf("    ");
    for (i = 0; i < col; i++)
    {
        printf("%4d", i);
    }
    printf("\n");
    for (i = 0; i < row; i++)
    {
        for (k = 0; k < SizeCaseRow; k++)
        {
            if (k == SizeCaseRow / 2)
            {
                printf("%4d", i);

                for (j = 0; j < col; j++)
                {
                    if (TabEtat[i * col + j] == 1)
                    {
                        if (TabMemory[i * col + j] > 'A' && TabMemory[i * col + j] < 'G')
                        {
                            Color(TabEtat[i * col + j] % 66 + 1, BLACK);
                        }
                        if (TabMemory[i * col + j] > 'G' && TabMemory[i * col + j] < 'M')
                        {
                            Color(TabMemory[i * col + j] % 72 + 1, BLACK);
                        }
                        if (TabMemory[i * col + j] > 'M' && TabMemory[i * col + j] < 'S')
                        {
                            Color(TabMemory[i * col + j] % 78 + 1, BLACK);
                        }
                        if (TabMemory[i * col + j] > 'S' && TabMemory[i * col + j] < 'Y')
                        {
                            Color(TabMemory[i * col + j] % 84 + 1, BLACK);
                        }
                        if (TabMemory[i * col + j] == 'A' || TabMemory[i * col + j] == 'G' || TabMemory[i * col + j] == 'M' || TabMemory[i * col + j] == 'S' || TabMemory[i * col + j] == 'Y')
                        {
                            Color(0, BLACK);
                        }
                        if (TabMemory[i * col + j] == 'B')
                        {
                            Color(1, BLACK);
                        }
                        printf("%4c", TabMemory[i * col + j]);
                        Color(WHITE, BLACK);
                    }
                    else
                    {
                        printf("%4c", '?');
                    }
                }
            }
            else
            {
                printf("\n");
            }
        }
        printf("\n");
    }
}

void Color(int text, int fond)
{
    int text_color = 0;
    int fond_color = 0;
#if defined(WIN32) || defined(WIN64)
    // to change the color of a Windows terminal
    switch (text)
    {
    case RED:
        text_color = 12;
        break;
    case GREEN:
        text_color = 10;
        break;
    case BLUE:
        text_color = 9;
        break;
    case YELLOW:
        text_color = 14;
        break;
    case PURPLE:
        text_color = 5;
        break;
    case CYAN:
        text_color = 11;
        break;
    case WHITE:
        text_color = 15;
        break;
    case BLACK:
        text_color = 0;
        break;
    }
    switch (fond)
    {
    case RED:
        fond_color = 12;
        break;
    case GREEN:
        fond_color = 10;
        break;
    case BLUE:
        fond_color = 9;
        break;
    case YELLOW:
        fond_color = 14;
        break;
    case PURPLE:
        fond_color = 5;
        break;
    case CYAN:
        fond_color = 11;
        break;
    case WHITE:
        fond_color = 15;
        break;
    case BLACK:
        fond_color = 0;
        break;
    }
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, fond_color * 16 + text_color);
#else
    // to change the color of an ANSI terminal
    switch (text)
    {
    case RED:
        text_color = 31;
        break;
    case GREEN:
        text_color = 32;
        break;
    case BLUE:
        text_color = 34;
        break;
    case YELLOW:
        text_color = 33;
        break;
    case PURPLE:
        text_color = 35;
        break;
    case CYAN:
        text_color = 36;
        break;
    case WHITE:
        text_color = 37;
        break;
    case BLACK:
        text_color = 30;
        break;
    default:
        text_color = text;
        break;
    }
    switch (fond)
    {
    case RED:
        fond_color = 41;
        break;
    case GREEN:
        fond_color = 42;
        break;
    case BLUE:
        fond_color = 44;
        break;
    case YELLOW:
        fond_color = 43;
        break;
    case PURPLE:
        fond_color = 45;
        break;
    case CYAN:
        fond_color = 46;
        break;
    case WHITE:
        fond_color = 107;
        break;
    case BLACK:
        fond_color = 0;
        break;
    }
    printf("\033[0;"
           "%d"
           ";"
           "%dm",
           text_color, fond_color);
#endif
}

void myfflush(void)
{
    char c = 0;

    while (c != '\n')
    {
        c = getchar();
    }
}

void Pause(void)
{
    char keypressed;
    keypressed = getchar();
    if (keypressed != '\n')
    {
        myfflush();
    }
}

int mygets(char *pS, int cap)
{
    int lg = 0;

    fgets(pS, cap, stdin);
    lg = strlen(pS);
    if (pS[lg - 1] == '\n')
    {
        lg--;
        pS[lg] = '\0';
    }
    else
    {
        myfflush();
    }

    return lg;
}

void PrintWelcomeScreen(void)
{
    system("cls");

    // Print title
    printf("**********************************************\n");
    printf("*               Memory Game                  *\n");
    printf("**********************************************\n");

    // Print author
    printf("\nAuthor: AbyssBagel aka Antonin G.\n");

    // Print date
    // You can use the time.h library to get the current date
    // Replace the following line with your preferred way of getting the current date
    printf("Date: 01/2022\n");

    // Mention to press enter to start
    printf("\nPress Enter to start...");

    // Wait for Enter key
    while (getchar() != '\n')
    {
    }

    // Clear the console again
    system("cls");
}

// zehgfizjebfjizeb
