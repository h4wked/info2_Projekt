#include <stdlib.h>
#include <stdio.h>

#include "datastructure.h"
#include "tools.h"
#include "team.h"
#include "list.h"
#include "search.h"
#include "sort.h"

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
        "Hash-Tabelle auflisten",
        "Programm beenden"
    };

    int choice;
    load(SAVEFILE);                 /*LADEN*/

    do{
        choice = getMenu("Mannschaftsverwaltung V0.01", menu, 9);

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
            TTeam * currentTeam = choseTeam();
            if (currentTeam == NULL) break;
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
            do
            {
                clearScreen();
                TTeam * chosenTeam = choseTeam();
                if(chosenTeam == NULL) break;
                deletePlayer(chosenTeam);
            }
            while(askYesOrNo("Moechten Sie einen weiteren Spieler loeschen? (j/n)") == EXIT_SUCCESS);
            break;
        case 4:
            printf("deleteTeam\n");
            printLine('-', 30);
            while(deleteTeam() != EXIT_SUCCESS) {
                clearScreen();
                char sentence[] = "Sind Sie sicher das Sie das Team loeschen moechten? (j/n)";
                if(askYesOrNo(sentence) == EXIT_SUCCESS)
                {
                    clearScreen();
                    continue;
                }
                else
                {
                    break;
                }
                free(sentence);
                oneTeamCleanup(currentTeam);
            }
            break;
        case 5:
            printf("Spielersuche\n");
            printLine('-', 30);
            printf("Geben Sie den Namen des Spielers ein den Sie suchen:\n-> ");
            TPlayer player;
            player.name = calloc(MAXNAMELENGTH, sizeof(char));
            scanf("%39[^\n]", player.name);
            TListElement * searchResult = search(PlayerIndex, nameSort, &player);
            if(searchResult == NULL)
            {
                printf("\n\nSpieler mit dem gesuchten Namen nicht gefunden.\n");
            }
            else
            {
                printf("\nin der Mannschaft %s:\n\t", searchResult->Team->name);
                listOnePlayer(searchResult->Player);
            }
            clearBuffer();
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
            clearScreen();
            printf("Hash-Tabelle\n");
            printLine('=', 12);
            printf("\nHashwert  |  Mannschaft\t\t\t | Spieler\n");
            printLine('-', 80);
            for(int c = 0; c < MAXINDEX; c++)
            {
                if(PlayerIndex[c].first != NULL)
                {
                    printf("      %3d | ", c);
                    int len = 29 - strlen(PlayerIndex[c].first->Team->name);
                    printf("%s", PlayerIndex[c].first->Team->name);
                    for(int i = 0; i < len; i++)
                        printf(" ");
                    printf("| %s\n", PlayerIndex[c].first->Player->name);
                    TListElement * currentElement = PlayerIndex[c].first;
                    while(currentElement->next != NULL)
                    {
                        currentElement = currentElement->next;
                        printf("          | ", c);
                        int len = 29 - strlen(currentElement->Team->name);
                        printf("%s", currentElement->Team->name);
                        for(int i = 0; i < len; i++)
                            printf(" ");
                        printf("| %s\n", currentElement->Player->name);
                    }
                }
            }
            break;
        case 9:
            printf("Programm wird beendet!\n");
            save(SAVEFILE);
            teamCleanup();
            break;
        }
        waitForEnter();

    }while(choice != 9);
}
