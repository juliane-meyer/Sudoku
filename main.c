#include <stdio.h>
#include <stdlib.h>h


// Willkommens Nachricht
int main()
{
    printf("Hello to sudoku!\n");
    menu();

    int aktiv = 1;

    do {
        aktiv = menueeingabe();       // Wenn das Spiel aktiv ist, soll immer Funktion ausgeführt werden.
    } while (aktiv);                   // Wenn nicht soll die Schleife beendet werden.
    return 0;
}

int sudoku[9][9];                   // Globale Varibalen
int aktiv = 1;
int difficulty;

// Menü um auszuwählen, was man möchte. Neues Spiel oder es beenden.
void menu()
{
    char ch;

    printf("Menu:\n");
    printf("1. Neues Spiel\n");
    printf("2. Ende\n");
    printf("Bitte Auswahl treffen: ");

    do {
        ch = getchar();
    } while(ch != '1' && ch != '2');    // Wenn was anderes als 1 eingeben wird, soll die Abfrage nochmal durchlaufen
    if (ch == '1') {
        menuNewGame();                  // Bei 1 soll das neue Spiel aufgerufen werden.
    } else if (ch == '2') {             // Bei 2 soll alles beendet werden
        return;
    }
}

void menuNewGame()
{
    char ch;

    printf("Menu:\n");                  // Auswahl der Spiel - Schwirigkeitsgrade
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
    FILE *fp = NULL;                    // Variablendeklaration

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

    int column = 0;
    int row = 0;

    for (column = 0; column < 108; column++){                                         // das gleich mit row
            c = fgetc(fp);
            if (c != ' ' && c!= '\n'){
                sudoku[row][column] = (int)c - 48;
            }
            if (c == '\n') {
                row++;
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
                printf("|"); // separator after every 3 numbers
            }

            if (sudoku[row][column] == 0) {
            printf(" . "); // placeholder for empty numbers
            } else {
                printf(" %i ", sudoku[row][column]); // print out number
            }
        }

    printf("|\n"); // last separator after each row and new line
    }
    printf(" +---------+---------+---------+\n");
}

// Neue Menüeingabe. Was will man mit dem Sudoku machen?

int menueeingabe()
{
    char ch;

    printf("Menue:\n");
    printf("1. Neues Spiel\n");     // To Do: andere Spiele einfügen
    printf("2. spielen \n");
    printf("3. Ende\n");
    printf("Bitte Auswahl treffen: ");

    ch=getchar();

    switch(ch){
        case '1':menuNewGame();break;
        case '2':eingabeSudoku();break;
        case '3':return 0; break;
        default:menueeingabe();
    }
    return 1;
}

void eingabeSudoku() {

    int column;
    int row;
    int number;

    do {
        do{
            printf("Zeile: "); // oben nach unten
            scanf("%u",&row);
        } while (checkInput(row)!= 1);

        do{
            printf("Spalte: "); // Links nach rechts
            scanf("%u",&column);
        } while (checkInput(column)!= 1);

    } while (sudoku[row-1][column-1] != 0);


        do{
            printf("Eingabe: ");
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

//Anzeige für Lösung


void solution() {

    int solutionsudoku[9][9];
    char c;
    FILE *fp = fopen(".\\Lösungeasy1.txt", "r");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int column;
    int row;

    for (row = 0; row < 9; row++){
        for (column = 0; column < 9; column++){                                         // das gleich mit row
            c = fgetc(fp);
            //if (c == '\n') continue;
            solutionsudoku[row][column] = (int)c - 48;
        }
    }

    fclose(fp);

    for (row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            printf("+---------+---------+---------+\n");
        }

        for(column = 0; column < 9; column++) {
            if (column % 3 == 0) {
            printf("|"); // separator after every 3 numbers
            }

            if (sudoku[row][column] == 0) {
            printf(" . "); // placeholder for empty numbers
            } else {
                printf(" %i ", solutionsudoku[row][column]); // print out number
            }
        }

    printf("|\n"); // last separator after each row and new line
    }
    printf("+---------+---------+---------+\n");
}



