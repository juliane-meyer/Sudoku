#include <stdio.h>
#include <stdlib.h>h


// Willkommens Nachricht
int main()
{
    printf("Hello to sudoku!\n");
    menu();

    int aktiv = 1;

    do {
        aktiv = menueeingabe();
    } while (aktiv);
    return 0;
}

int boolSudoku [9][9];
int sudoku [9][9];
int aktiv = 1;
int difficulty;


void menu()
{
    char ch;

    printf("Menu:\n");
    printf("1. Neues Spiel\n");
    printf("2. Ende\n");
    printf("Bitte Auswahl treffen: ");

    do {
        ch = getchar();
    } while(ch != '1' && ch != '2');
    if (ch == '1') {
        menuNewGame();
    } else if (ch == '2') {
        return;
    }
}

void menuNewGame()
{
    char ch;

    printf("Menu:\n");
    printf("1. Leicht\n");
    printf("2. Mittel\n");
    printf("3. Schwer\n");
    printf("Bitte Auswahl treffen: ");

    do {
        ch = getchar();
    } while(ch != '1' && ch != '2' && ch != '3');

    createSudoku(ch);
}

// Sudoku wird ausgeben
void createSudoku(char difficulty) {

    char c;
    FILE *fp = NULL;
    if (difficulty == '1') {
        fp =fopen(".\\easy1.txt", "r");
    } else if (difficulty == '2') {
        fp =fopen(".\\middle1.txt", "r");
    } else if (difficulty == '3') {
        fp =fopen(".\\hard1.txt", "r");
    }

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int column;
    int row;

    for (row = 0; row < 9; row++){
        for (column = 0; column < 9; column++){
            c = fgetc(fp);
            if((int)c - 48 == 0) {
                boolSudoku[row][column] = 1;
            } else {
                boolSudoku[row][column] = 0;
            }
            sudoku[row][column] = (int)c - 48;
        }
    }

    fclose(fp);

    printSudoku();
}

void printSudoku(){

    int column;
    int row;
    char k='A';

    printf("   1  2  3   4  5  6   7  8  9\n");
    for (row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            printf(" +---------+---------+---------+\n");
        }
        printf("%c",k);
        k++;

        for(column = 0; column < 9; column++) {
            if (column % 3 == 0) {
                printf("|");
            }

            if (sudoku[row][column] == 0) {
            printf(" . ");

            } else {
                printf(" %i ", sudoku[row][column]);
            }
        }

    printf("|\n");
    }
    printf(" +---------+---------+---------+\n");
}

// Neue Menueeingabe. Was will man mit dem Sudoku machen?

int menueeingabe()
{
    char ch;

    printf("Menue:\n");
    printf("1. Neues Spiel\n");     // To Do: andere Spiele einf�gen
    printf("2. spielen \n");
    printf("3. Ende\n");
    printf("Bitte Auswahl treffen: ");

    do {
        ch = getchar();
    } while(ch != '1' && ch != '2' && ch != '3' && ch != '4');

    if (ch == '1') {
        menuNewGame();
    } else if (ch == '2') {
        eingabeSudoku();
    } else if (ch == '3') {
        return 0;
    }
    return 1;
}

void eingabeSudoku() {

    int column;
    int row;
    int number;

    do{
        printf("Feld eingeben:");  // 1.Zahl A-Z; 2.Zahl 1-9  Funktioniert nur mit Leerzeichen zwischen den Zahlen.
        scanf("%u%u",&row, &column);
    } while (checkField(row, column) != 1);


    do{
         printf("Loesung: ");
         scanf("%u",&number);
    } while (checkInput(number)!= 1);

        sudoku[row-1][column-1]= number;

        printSudoku();
}

int checkInput(int number) {
    if(number <= 9 && number >= 1 ){
        return 1;
    }
    return 0;
}

int checkField(int row, int column) {

    if(boolSudoku[row-1][column-1] == 1) {
        return 1;
    } else {
        printf("\nDieses Feld kann nicht veraendert werden! \n");
        return 0;
    }
}
