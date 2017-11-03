#include <stdlib.h>
#include <stdio.h>

#include <menu.h>


int main(int argc, char * argv[]) {

    char * menu[] = {
        "1. Neue Mannschaft anlegen",
        "2. Spieler hinzufuegen",
        "3. Spieler loeschen",
        "4. Mannschaft loeschen",
        "5. Suchen",
        "6. Sortieren",
        "7. Auflisten",
        "8. Programm beenden"
    };

    int choice;

    while(choice != 8){
        choice = getMenu("Mannschaftsverwaltung V0.01", menu, 8);

        switch(choice) {

        case 1:
            printf("Neue Mannschaft anlegen\n");
            printLine('-', 30);
            break;
        case 2:
            printf("Spieler hinzufuegen\n");
            printLine('-', 30);
            break;
        case 3:
            printf("Spieler loeschen\n");
            printLine('-', 30);
            break;
        case 4:
            printf("Suchen\n");
            printLine('-', 30);
            break;
        case 5:
            printf("Neue Mannschaft anlegen\n");
            printLine('-', 30);
            break;
        case 6:
            printf("Neue Mannschaft anlegen\n");
            printLine('-', 30);
            break;
        case 7:
            printf("Neue Mannschaft anlegen\n");
            printLine('-', 30);
            break;
        }
        printf("\nBitte Eingabetaste drücken!\n");
        char enter = 0;
        clearBuffer();
        while( getchar() != '\n' );
    }
}
