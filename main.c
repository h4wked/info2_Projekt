#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"
#include "menu.h"
#include "tools.h"
#include "team.h"

#define SAVEFILE "teams.xml"

int TeamCounter = 0;
TTeam Teams[MAXTEAMS];

int main(int argc, char * argv[]) {


    char * menu[] = {
        "Neue Mannschaft anlegen",
        "Spieler hinzufuegen",
        "Spieler loeschen",
        "Mannschaft loeschen",
        "Suchen",
        "Sortieren",
        "Auflisten",
        "Programm beenden"
    };

    int choice;
    load(SAVEFILE);                 /*LADEN*/

    do{
        choice = getMenu("Mannschaftsverwaltung V0.01", menu, 8);

        switch(choice) {

        case 1:
            printf("createTeam\n");
            printLine('-', 30);

            while(createTeam() != EXIT_SUCCESS) {               /*Fehlerbehandlung falls createTeam fehlschlägt*/
                clearScreen();
                char phrase[] = "Erstellung eines Teams fehlgeschlagen! Soll Sie wiederholt werden? (j/n)";
                if(askYesOrNo(phrase) == EXIT_SUCCESS){         /*Frage ob Teamerstellung wiederholt werden soll*/
                    clearScreen();
                    continue;
                }else{
                    break;
                }
                free(phrase);
            }
            TeamCounter++;
            break;
        case 2:
            printf("addPlayer\n");
            printLine('-', 30);
            clearScreen();
            char ** teamNames = calloc(TeamCounter, sizeof(char));
            for(int i = 0; i < TeamCounter; i++){
                    printf("%s\n", (Teams + i)->name);
              teamNames[i] = (Teams + i)->name;
            }
            int teamNum = getMenu("Waelen Sie das Team, zudem Sie einen Spieler hinzufuegen moechten!", teamNames, TeamCounter);
            do {
                if(createPlayer(teamNum) == EXIT_SUCCESS) {
                    Teams[teamNum].numberOfPlayers++;
                }else{
                    printf("\nSpielereingabe Fehlgeschlagen!\n");
                    sleep(1);
                }
            }while(askYesOrNo("\n\nMoechten Sie einen weiteren Spieler eingeben? (j/n)") == EXIT_SUCCESS);
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
            sortTeams(choice);
            break;
        case 7:
            printf("listTeams\n");
            printLine('-', 30);
            listTeams();
            break;
        case 8:
            printf("Programm wird beendet!\n");
            save(SAVEFILE);
            teamCleanup();
            break;
        }
        waitForEnter();

    }while(choice != 8);
}
