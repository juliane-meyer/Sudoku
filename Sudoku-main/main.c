#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Willkommens Nachricht

int main()
{
    printf("Hello to sudoku!\n");
    menu();

    int aktiv = 1;

    do {                            // Solange das Spiel aktiv ist, soll die Schleife durchlaufen.
        aktiv = menueeingabe();
    } while (aktiv);
    return 0;
}

// Globale Variablen

int boolSudoku [9][9];
int sudoku [9][9];
int aktiv = 1;
char difficulty;
int lastGame = 0;
time_t startTime;
time_t endTime;

// Startmenü - Kommt nur am Anfang

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

// Menü fragt nach dem Schwierigkeitsgrad.

void menuNewGame()
{
    char ch;

    printf("Menu:\n");
    printf("1. Leicht\n");
    printf("2. Mittel\n");
    printf("3. Schwer\n");
    printf("Bitte Auswahl treffen: ");

    do {
        difficulty = getchar();
    } while(difficulty != '1' && difficulty != '2' && difficulty != '3');

    createSudoku();
}

// Hier werden zu jeder Schwierigkeitsstufe 3 Spiele gespeichert und random ausgegeben, bei "neues Spiel" spielen.

void createSudoku() {
    char c;
    FILE *fp = NULL;
    int randSpiel;

    do {
        randSpiel = rand() % 3 + 1;         // Würde bei 0 anfangen. Mit +1 fängt er bei 1 an.
    } while(randSpiel == lastGame);
    lastGame = randSpiel;

    if (difficulty == '1') {
        switch(randSpiel) {
        case 1: fp =fopen(".\\easy1.txt", "r"); break;
        case 2: fp =fopen(".\\easy2.txt", "r"); break;
        case 3: fp =fopen(".\\easy3.txt", "r"); break;
        }
    } else if (difficulty == '2') {
        switch(randSpiel) {
        case 1: fp =fopen(".\\middle1.txt", "r"); break;
        case 2: fp =fopen(".\\middle2.txt", "r"); break;
        case 3: fp =fopen(".\\middle3.txt", "r"); break;
        }
    } else if (difficulty == '3') {
        switch(randSpiel) {
        case 1: fp =fopen(".\\hard1.txt", "r"); break;
        case 2: fp =fopen(".\\hard2.txt", "r"); break;
        case 3: fp =fopen(".\\hard3.txt", "r"); break;
        }
    }

    time(&startTime);

    if (fp == NULL)                                     // Wenn in der Datei nichts ist, soll dieFehlermeldung ausgeben werden.
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int column;
    int row;

    for (row = 0; row < 9; row++){                      // Die Zahlen in der Datei werden formatiert
        for (column = 0; column < 9; column++){
            c = fgetc(fp);
            if((int)c - 48 == 0) {
                boolSudoku[row][column] = 1;            // Bei einer Null in der Datei, ist die Zahl veränderbar.
            } else {
                boolSudoku[row][column] = 0;            // Wenn keine Null darin steht, ist sie nicht veränderbar.
            }
            sudoku[row][column] = (int)c - 48;
        }
    }

    fclose(fp);

    printSudoku();
}

// Das Soduku wird kreiert und ausgegeben

void printSudoku(){

    int column;
    int row;
    int k = 1;

    printf("    1  2  3   4  5  6   7  8  9\n");
    for (row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            printf("  +---------+---------+---------+\n");
        }
        printf("%d ",k);
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
    printf("  +---------+---------+---------+\n");
}

// Neue Menueeingabe. Was will man mit dem Sudoku machen?

int menueeingabe()
{
    char ch;

    printf("Menue:\n");
    printf("1. Neues Spiel\n");
    printf("2. spielen \n");
    printf("3. Spiel pruefen \n");
    printf("4. Ende\n");
    printf("Bitte Auswahl treffen: ");

    do {
        ch = getchar();
    } while(ch != '1' && ch != '2' && ch != '3' && ch != '4');

    if (ch == '1') {
        menuNewGame();
    } else if (ch == '2') {
        eingabeSudoku();
    } else if (ch == '3') {
        pruefeSpiel();
    } else if (ch == '4') {
        time(&endTime);
        printf("Sie haben fuer dieses Spiel %d Sekunden gebraucht! \n", endTime-startTime);
        return 0;
    }
    return 1;
}

// Ist wird die Feldauswahl abgefragt und die neue Eingabe.

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
        time(&endTime);
        printf("Sie haben bislang fuer dieses Spiel %d Sekunden gebraucht! \n", endTime-startTime);
        printSudoku();
}

// Checkt, ob eine Zahl zwischen einschließlich 1 - 9 eingegeben wurde.

int checkInput(int number) {
    if(number <= 9 && number >= 1 ){
        return 1;
    }
    return 0;
}

// Checkt, ob das Feld verändern werden darf.

int checkField(int row, int column) {

    if(boolSudoku[row-1][column-1] == 1) {
        return 1;
    } else {
        printf("\nDieses Feld kann nicht veraendert werden! \n");
        return 0;
    }
}

void pruefeSpiel() {
    FILE *loesungenFile = NULL;

    if ((int)difficulty-48 == 1) {
        switch(lastGame) {
        case 1: loesungenFile =fopen(".\\Loesungeasy1.txt", "r"); break;
        case 2: loesungenFile =fopen(".\\Loesungeasy2.txt", "r"); break;
        case 3: loesungenFile =fopen(".\\Loesungeasy3.txt", "r"); break;
        }
    } else if ((int)difficulty-48 == 2) {
        switch(lastGame) {
        case 1: loesungenFile =fopen(".\\Loesungmiddle1.txt", "r"); break;
        case 2: loesungenFile =fopen(".\\Loesungmiddle2.txt", "r"); break;
        case 3: loesungenFile =fopen(".\\Loesungmiddle3.txt", "r"); break;
        }
    } else if ((int)difficulty-48 == 3) {
        switch(lastGame) {
        case 1: loesungenFile =fopen(".\\Loesunghard1.txt", "r"); break;
        case 2: loesungenFile =fopen(".\\Loesunghard2.txt", "r"); break;
        case 3: loesungenFile =fopen(".\\Loesunghard3.txt", "r"); break;
        }
    }

    if (loesungenFile == NULL)                                     // Wenn in der Datei nichts ist, soll dieFehlermeldung ausgeben werden.
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int loesungcolumn;
    int loesungrow;
    char c;
    int fail = 0;

    for (loesungrow = 0; loesungrow < 9; loesungrow++){                      // Die Zahlen in der Datei werden formatiert
        if (fail == 1) {
            break;
        }

        for (loesungcolumn = 0; loesungcolumn < 9; loesungcolumn++){
            c = fgetc(loesungenFile);
            if (sudoku[loesungrow][loesungcolumn] != (int)c - 48) {
                printf("\nDie Loesung an der Stelle %d,%d ist nicht korrekt! aktueller Wert %d \n\n", loesungrow+1, loesungcolumn+1, sudoku[loesungrow][loesungcolumn]);
                fail = 1;
                break;
            }

        }
    }

    fclose(loesungenFile);
    menueeingabe();
}

//
