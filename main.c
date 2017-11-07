#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"
#include "menu.h"
#include "tools.h"
#include "team.h"

int TeamCounter = 0;
TTeam Teams[MAXTEAMS];

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

    do{
        choice = getMenu("Mannschaftsverwaltung V0.01", menu, 8);

        switch(choice) {

        case 1:
            printf("createTeam\n");
            printLine('-', 30);
            waitForEnter();

            while(createTeam() != EXIT_SUCCESS) {               /*Fehlerbehandlung falls createTeam fehlschlägt*/
                char phrase[] = "Erstellung eines Teams fehlgeschlagen!\nSoll Sie wiederholt werden?\n";
                if(askYesOrNo(phrase) == EXIT_SUCCESS){         /*Frage ob Teamerstellung wiederholt werden soll*/
                    clearScreen();
                    continue;
                }else{
                    TeamCounter++;
                }
                free(phrase);
            }
            break;
        case 2:
            printf("addPlayer\n");
            printLine('-', 30);
            break;
        case 3:
            printf("deletePlayer\n");
            printLine('-', 30);
            break;
        case 4:
            printf("deleteTeam\n");
            printLine('-', 30);
            break;
        case 5:
            printf("searchPlayer\n");
            printLine('-', 30);
            break;
        case 6:
            printf("sortTeams\n");
            printLine('-', 30);
            break;
        case 7:
            printf("listTeams\n");
            printLine('-', 30);
            break;
        case 8:
            printf("Programm wird beendet!\n");
            break;

        }
        waitForEnter();

    }while(choice != 8);
}
