#include <stdlib.h>
#include <stdio.h>

#include <menu.h>


int main(int argc, char * argv[]) {

    char * menu[] = {
        "1. Neue Mannschaft anlegen"
        "2. Spieler hinzufuegen"
        "3. Spieler loeschen"
        "4. Mannschaft loeschen"
        "5. Suchen"
        "6. Sortieren"
        "7. Auflisten"
        "8. Programm beenden"
    };

    int choice;

    while(choice != 8){
        choice = getMenu("Mannschaftsverwaltung V0.01", menu, 8);
    }
}
