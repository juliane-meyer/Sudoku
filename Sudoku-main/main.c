#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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

    do {                                    // Nur bei richtiger Eingabe, von 1 oder 2 geht es weiter.
        ch = getchar();
    } while(ch != '1' && ch != '2');
    if (ch == '1') {                        // Die Eingabe 1 fürht zu einem weiteren Menü, die Eingabe 2 beendet die Aussgabe.
        menuNewGame();
    } else if (ch == '2') {
        return;
    }
}

// Menü fragt nach dem Schwierigkeitsgrad / ob man ein eingespeichertes Spiel spielen will.

void menuNewGame()
{
    char ch;

    printf("Menu:\n");
    printf("1. Leicht\n");
    printf("2. Mittel\n");
    printf("3. Schwer\n");
    printf("4. Benutzerdefiniert\n");
    printf("Bitte Auswahl treffen: ");

    do {
        difficulty = getchar();                     // nur die Eingabe 1,2,3 und 4 ist korrekt. Bei einer falschen Eingabe fragt das Programm nochmal.
    } while(difficulty != '1' && difficulty != '2' && difficulty != '3' && difficulty != '4');

    createSudoku();
}

// Hier werden zu jeder Schwierigkeitsstufe 3 Spiele gespeichert und random ausgegeben, wenn man "neues Spiel" spielen auswählt.
// Bei der Eingabe 4 wird kann der Spielstand in eine Datei eingespeichert werden.

void createSudoku() {

    char c;
    FILE *fp = NULL;
    int randGame;

    do {
        randGame = rand() % 3 + 1;                 // Würde bei 0 anfangen. Mit + 1 fängt er bei 1 an. Das Spiel wird random ausgewählt.
    } while(randGame == lastGame);

    lastGame = randGame;

    if (difficulty == '1') {
        switch(randGame) {
        case 1: fp =fopen(".\\easy1.txt", "r"); break;
        case 2: fp =fopen(".\\easy2.txt", "r"); break;
        case 3: fp =fopen(".\\easy3.txt", "r"); break;
        }
    } else if (difficulty == '2') {
        switch(randGame) {
        case 1: fp =fopen(".\\middle1.txt", "r"); break;
        case 2: fp =fopen(".\\middle2.txt", "r"); break;
        case 3: fp =fopen(".\\middle3.txt", "r"); break;
        }
    } else if (difficulty == '3') {
        switch(randGame) {
        case 1: fp =fopen(".\\hard1.txt", "r"); break;
        case 2: fp =fopen(".\\hard2.txt", "r"); break;
        case 3: fp =fopen(".\\hard3.txt", "r"); break;
        }
    } else if (difficulty == '4') {
        do {                                            // Hier wird eine gültige Datei abgefragt, ob ein Benutzerdefiniertes Sudoku wieder ausgeben zu können.
            char name[20];                              // Wenn es die Datei nicht gibt, fragt die Schleife nochmal.
            printf("Bitte geben Sie einen gueltigen Dateinamen ein: ");
            scanf("%s", name);
            printf("Die Datei %s wird eingelesen \n", name);
            char file[23] = ".\\";                      // Der Datwiname wird eingelesen.
            strcat(file, name);
            fp =fopen(file, "r");                       // Die Datei wird zum Bearbeiten ausgegeben.
        } while(fp == NULL);
    }

    time(&startTime);

    if (fp == NULL) {                                   // Wenn in der Datei nichts ist, soll die Fehlermeldung ausgeben werden.
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int column;
    int row;

    for (row = 0; row < 9; row++){
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

    printSudoku();                                      // Hier ist der Aufruf, dass das Sudoku ausgeben wird.
}

// Das Soduku wird in einem 9 x 9 Feldern kreiert und in ausgegeben.

void printSudoku(){

    int column;
    int row;
    int scale = 1;

    printf("    1  2  3   4  5  6   7  8  9\n");
    for (row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            printf("  +---------+---------+---------+\n");
        }
        printf("%d ",scale);
        scale++;

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

// Nach der Ausgabe, erfolgt ein neues Menue.
// Was will man mit dem Sudoku machen?

int menueeingabe()
{
    char ch;

    printf("Menue:\n");
    printf("1. Neues Spiel\n");
    printf("2. spielen \n");
    printf("3. Spiel pruefen \n");
    printf("4. Spiel speichern \n");
    printf("5. Ende\n");
    printf("Bitte Auswahl treffen: ");

    do {
        ch = getchar();
    } while(ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5');

    if (ch == '1') {
        menuNewGame();
    } else if (ch == '2') {
        eingabeSudoku();
    } else if (ch == '3') {
        pruefeSpiel();
    } else if (ch == '4') {
        speichereSpiel();
    } else if (ch == '5') {
        time(&endTime);
        printf("Sie haben fuer dieses Spiel %d Sekunden gebraucht! \n", endTime-startTime);     // Die Zeit, die man schon beim Spielen gebraucht hat, wird einem angezeigt.
        return 0;                                                                               // Es werden nur Sekunden angezeigt.
    }
    return 1;
}

// Hier wird die Feldauswahl abgefragt und es wird eine Eingabe für das Feld abgefragt.

void eingabeSudoku() {

    int column;
    int row;
    int number;

    do{
        printf("Feld eingeben:");                   // Erst von oben nach unten, dann die Zahl von links nach rechts. !!! Funktioniert nur mit Leerzeichen zwischen den Zahlen. !!!
        scanf("%d%d",&row, &column);
    } while (checkField(row, column) != 1);         // Hier wird die Funktion angewendet, die prüft, ob die Eingabe auch erlaubt ist.

    do{
        printf("Loesung: ");
        scanf("%d",&number);
    } while (checkInput(number)!= 1);               // Hier wird die Funktion angewendet, die prüft, ob die Eingabe eine Zahl zwischen 1 und 9 ist.

        sudoku[row-1][column-1]= number;
        time(&endTime);
        printf("Sie haben bislang fuer dieses Spiel %d Sekunden gebraucht! \n", endTime-startTime);     // Die Gesamtzeit, die man beim spielen gebraucht hat, wird einem angezeigt.
        printSudoku();                                                                                  // Es werden nur Sekunden angezeigt.
}

// Checkt, ob eine Zahl zwischen einschließlich 1 - 9 eingegeben wurde.

int checkInput(int number) {
    if(number <= 9 && number >= 1 ){
        return 1;
    } else {
        printf("Geben Sie eine gueltige Zahl ein! \n");        // Bug: Bei der Eingabe von Buchstaben fliegt einem das Ding um die Ohren!
        return 0;
    }
}

// Checkt, ob das Feld verändern werden darf.

int checkField(int row, int column) {

    if(boolSudoku[row-1][column-1] == 1) {
        return 1;
    } else {
        printf("Dieses Feld kann nicht veraendert werden! \n");  // Bug: Bei der eingabe von Buchstaben fliegt einem das Ding um die Ohren!
        return 0;
    }
}

// Prüft, ob die Eingabe in einem Feld richtig ist. Dabei wird Feld für Feld vorgegangen.

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
        }                                                                   // BUG: Die Prüfung ist leider nicht mehr möglich für Spiele, die mal gespeichert wurden.
    } else if ((int)difficulty-48 == 4) {
        printf("Bei einem Benutzerdefinierten Spiel ist keine Pruefung moeglich. Bitte starten Sie ein neues Spiel\n");
        menueeingabe();
    }

    if (loesungenFile == NULL)  {                                         // Wenn in der Lösungsdatei nichts ist, soll dieFehlermeldung ausgeben werden.
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

// Globale Varibalen für die Erkennung und die Ausgabe der Lösung

    int loesungcolumn;
    int loesungrow;
    char c;
    int fail = 0;

    for (loesungrow = 0; loesungrow < 9; loesungrow++){                      // Die Zahlen in der Datei werden formatiert
        if (fail == 1) {
            break;
        }
// Hier wird man hingewiesen, ob die Lösung falsch ist und man wird gefragt, ob man die Lösung für das Feld anzeigen will.
        for (loesungcolumn = 0; loesungcolumn < 9; loesungcolumn++){
            c = fgetc(loesungenFile);
            int hint = 0;
            int loesung = c;
            if (sudoku[loesungrow][loesungcolumn] != (int)c - 48) {
                printf("\nDie Loesung an der Stelle %d,%d ist nicht korrekt! Aktueller Wert %d \n\n", loesungrow+1, loesungcolumn+1, sudoku[loesungrow][loesungcolumn]);

                printf("Soll ein Hinweis angezeigt werden? Ja(1) oder Nein(0):");
                scanf("%d", &hint);

                if ( hint = 1) {
                    printf("Die Loesung an der Stelle %d,%d ist nicht korrekt! Die Loesung lautet %d. \n\n", loesungrow+1, loesungcolumn+1, loesung - 48);
                }
                fail = 1;
                break;
            }

        }
    }
    // Die Datei wird geschlossen und die Menüeingabe wird wieder abgefragt.
    fclose(loesungenFile);
    menueeingabe();
}

// Hier wird die Datei, mit dem Spielstand, den man speichern will, in dem Ordner mit den anderen Datein hinzugefügt.

void speichereSpiel() {
    FILE *fp;
    char filename[100];
    char writestr[100];

    // Liest den Namen der Datei ein.
    printf("Bitte geben Sie den Dateinamen ein: ");
    scanf("%s", filename);

    // Datei wird im Schreibmodus geöffnet
    fp = fopen(filename,"w+");

    // Wenn die Datei erfolgreich geöffnet wurde, schreiben sich die Zeichenfolge in die Datei
    if ( fp )
    {
        uint32_t counter = 4;
        char buffer[16] = {0};

        for (int row = 0; row < 9; row++) {
            for (int column = 0; column < 9; column++) {
                int tmp = sudoku[row][column];
                sprintf(buffer, "%d", tmp);
                fputs(buffer, fp);
            }
        }
    // Wenn der Dateiname nicht richtig ist, wird einem das angezeigt.
    } else {
         printf("Datei kann nicht gespeichert werden. Bitte versuchen Sie es erneut.\n");
    }

    // Datei wird geschlossen
    fclose(fp);

    menueeingabe();
}
