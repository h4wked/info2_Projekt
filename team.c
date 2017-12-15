#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "datastructure.h"
#include "sort.h"
#include "tools.h"
#include "datetime.h"

/* TeamCounter und Teams[n].numberOfPlayers entprechen der physischen Anzahl an Spielern!! */

int createTeam() {

    clearScreen();
    printf("Erfassung einer neuen Mannschaft\n");
    printLine('=', 30);
    Teams[TeamCounter].numberOfPlayers = 0;                     /*initialize Players as 0*/

    if(getText("\nGeben Sie den Namen der Mannschaft ein!\n-> ", MAXNAMELENGTH, 0, &((Teams + TeamCounter)->name)) == EXIT_SUCCESS) {
    }else{
        memset(&Teams[TeamCounter], 0, sizeof(Teams[TeamCounter]));
        return EXIT_FAILURE;
    }

    if(getText("Geben Sie den Namen des Trainers ein!\n-> ", MAXNAMELENGTH, 1, &((Teams + TeamCounter)->coach)) == EXIT_SUCCESS) {
    }else{
        memset(&Teams[TeamCounter], 0, sizeof(Teams[TeamCounter]));
        return EXIT_FAILURE;
    }


    do {
        if(createPlayer() == EXIT_SUCCESS) {
            Teams[TeamCounter].numberOfPlayers++;
        }else{
            printf("\nSpielereingabe Fehlgeschlagen!\n");
            sleep(1);
        }

    }while(askYesOrNo("\n\nMoechten Sie einen weiteren Spieler eingeben? (j/n)") == EXIT_SUCCESS);

    return EXIT_SUCCESS;

}

void deleteTeam() {
}

int createPlayer() {

    int scanErg;
    printf("\nErfassung der Spieler\n");
    printLine('=', 30);
    int playerArrayNum = Teams[TeamCounter].numberOfPlayers;

    if((getText("Geben Sie den Namen des Spielers ein!\n-> ", MAXNAMELENGTH, 0, &((Teams + TeamCounter)->player[playerArrayNum].name))) == EXIT_FAILURE) {
       return EXIT_FAILURE;
       }         //Playername

    getDate("\nGeben Sie ggf. das Geburtsdatum des Spielers ein!\n", playerArrayNum);                                                 //Birthday

    int jerseyNr;
    printf("\nGeben Sie die Trikotnummer des Spielers ein!\n-> ");                                                                          //JerseyNum
    scanErg = scanf("%d", &jerseyNr);
    if(jerseyNr == 0) {
        printf("error trikotNr cant be 0!\n");
        return EXIT_FAILURE;
    }
    clearBuffer();

    if(scanErg <= 0) {
        printf("invalid input!\n");
        return EXIT_FAILURE;
    }else{
        Teams[TeamCounter].player[playerArrayNum].nr = jerseyNr;
    }
    return EXIT_SUCCESS;


}

void deletePlayer() {
}

void searchPlayer() {
}

void sortTeams(int choice) {
    char * sortmenu[] = {
                "Spieler nach Namen sortieren"
                "Spieler nach Geburtsdatum sortieren"
                "Spieler nach Trikotnr. Sortieren"
                "Spieler nach Anzahl geschossener Tore sortieren"
                "zurueck zum Hauptmenue"
            };
    choice = getMenu("Sortieren", sortmenu, 5);

    for(int i = 0; i < TeamCounter; i++) {
        switch(choice) {
                case 1:
                    teamQSort(nameSort);
                    break;
                case 2:
                    teamQSort(birthSort);
                    break;
                case 3:
                    teamQSort(trikotSort);
                    break;
                case 4:
                    teamQSort(goalSort);
                    break;
                case 5:
                    break;
                }
    }
}


void listTeams() {
    clearScreen();
    if(TeamCounter == 0) {
        printf("Keine Mannschaften vorhanden!\n");
    }else{
        printf("Liste der Mannschaften\n");
        printLine('=', 30);
        for(int c = 0; c < TeamCounter; c++) {
            listOneTeam(c);
        }
    }
}

void listOneTeam(int currentTeam) {
    printf("\nName:           : %s\n",Teams[currentTeam].name);

    if(Teams[currentTeam].coach != NULL) {
        printf("Trainer         : %s\n",Teams[currentTeam].coach);
    }

    printf("Anzahl Spieler  : %d\n", Teams[currentTeam].numberOfPlayers);

    printf("Spieler:\n");
    for(int c = 0; c < Teams[currentTeam].numberOfPlayers; c++) {
        printf("\t%2d: ",c+1);
        listOnePlayer(&(Teams[currentTeam].player[c]));
    }
}

void listOnePlayer(TPlayer * player) {

    printf("%s",player->name);
    printf(" (%d",player->nr);
    if(player->birthday != NULL) {
        printf(", * ");
        printDate(player->birthday);
        printf(")\n");
    }else{
        printf(")\n");
    }
}
