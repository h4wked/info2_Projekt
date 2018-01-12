#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"
#include "tools.h"
#include "team.h"
#include "list.h"

#include "menu.h"

#define SAVEFILE "teams.xml"

TTeam * firstTeam = NULL;
TTeam * lastTeam = NULL;

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
            break;
        case 2:
            clearScreen();
            printf("Liste der Mannschaften\n");
            printLine('=', 24);

            TTeam * currentTeam = firstTeam;
            int i = 1;
            while(currentTeam->nextTeam != NULL)            //Anzeigen aller Teams
            {
                printf("%d: %s\n", i, currentTeam->name);
                currentTeam = currentTeam->nextTeam;
                i++;
            }
            printf("%d: %s\n", i, currentTeam->name);

            int chosenTeam;
            while(1)
            {
                printf("\nWaehlen Sie ein Mannschaft (0 Abbruch) ", i, currentTeam->name);       //Auswählen des Teams
                int erg = scanf("%d", &chosenTeam);
                if(erg < 1 || chosenTeam < 0 || chosenTeam > i)            //ungültige Eingaben abfangen
                {
                    printf("Fehlerhafte Eingabe!\n");
                    continue;
                }
                else if(chosenTeam == 0)                                    //Abbruch
                {
                    break;
                }
                else
                {
                    currentTeam = firstTeam;                //springe zum ausgewählten Team
                    for(int c = 0; c < (chosenTeam-1); c++) currentTeam = currentTeam->nextTeam;
                    break;
                }
            }
            if(chosenTeam == 0) break;
            clearBuffer();

            do {
                if(createPlayer(currentTeam) == EXIT_SUCCESS) {
                    currentTeam->numberOfPlayers++;
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
            deleteTeam();
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
