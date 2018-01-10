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
        if(createPlayer(TeamCounter) == EXIT_SUCCESS) {
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

int createPlayer(int teamNum) {

    int scanErg;
    printf("\nErfassung eines Spielers\n");
    printLine('=', 30);
    if((Teams + teamNum)->numberOfPlayers >= MAXPLAYER){
        printf("Team hat maximale Anzahl an Spielern!\n");
        sleep(1);
        return EXIT_FAILURE;
    }
    int playerArrayNum = (Teams + teamNum)->numberOfPlayers;

    if((getText("Geben Sie den Namen des Spielers ein!\n-> ", MAXNAMELENGTH, 0, &((Teams + teamNum)->player[playerArrayNum].name))) == EXIT_FAILURE) {
       return EXIT_FAILURE;
       }         //Playername
    do{
    if(getDate("\nGeben Sie ggf. das Geburtsdatum des Spielers ein!\n", playerArrayNum, teamNum) == EXIT_SUCCESS) break;                                                 //Birthday
    }while(askYesOrNo("Erneut versuchen ein Geburtsdatum einzufügen? (j/n)") == EXIT_SUCCESS);

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
        Teams[teamNum].player[playerArrayNum].nr = jerseyNr;
    }
    return EXIT_SUCCESS;


}

void deletePlayer() {
}

void searchPlayer() {
}

void sortTeams() {
    int sortChoice;

    char * sortmenu[] = {
                "Spieler nach Namen sortieren",
                "Spieler nach Geburtsdatum sortieren",
                "Spieler nach Trikotnr. Sortieren",
                "Spieler nach Anzahl geschossener Tore sortieren",
                "zurueck zum Hauptmenue"
            };
    sortChoice = getMenu("Sortieren", sortmenu, 5);

        switch(sortChoice) {
                case 1:
                    sortTeam(nameSort);
                    break;
                case 2:
                    sortTeam(birthSort);
                    break;
                case 3:
                    sortTeam(trikotSort);
                    break;
                case 4:
                    sortTeam(goalSort);
                    break;
                case 5:
                    break;
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
        printf(", %d Tor(e) ", player->goals);
        printf(")\n");
    }else{
        printf(")\n");
    }
}
