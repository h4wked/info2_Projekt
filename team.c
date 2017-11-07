#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "datastructure.h"
#include "tools.h"
#include "datetime.h"


/* TeamCounter und Teams[n].numberOfPlayers entprechen der physischen Anzahl an Spielern!! */

int createTeam() {

    clearScreen();
    printf("Erfassung einer neuen Mannschaft\n");
    printLine('=', 30);
    Teams[TeamCounter].numberOfPlayers = 0;                     /*initialize Players as 0*/

    char * teamName = calloc(MAXNAMELENGTH, sizeof(char));      /*input Teamname*/

    printf("\nGeben Sie den Namen der Mannschaft ein!\n-> ");
    if(scanf("%s", teamName) > 0) {
        Teams[TeamCounter].name = teamName;
        clearBuffer();
    }else{
        printf("Invalid input!\n");
        sleep(2);
        free(teamName);
        memset(&Teams[TeamCounter], 0, sizeof(Teams[0])); /*cleanup invalid data*/
        return EXIT_FAILURE;
    }

    char *coachName = calloc(MAXNAMELENGTH, sizeof(char));      /*input Coachname */
    printf("Geben Sie den Namen des Trainers ein!\n-> ");
    if(scanf("%s", coachName) > 0) {
        clearBuffer();
        Teams[TeamCounter].name = teamName;
    }else{
        printf("Invalid input!\n");
        sleep(2);
        free(teamName);
        free(coachName);
        memset(&Teams[TeamCounter], 0, sizeof(Teams[0])); /*cleanup invalid data*/
        return EXIT_FAILURE;
    }

    do {
        if(createPlayer() == EXIT_SUCCESS) {
            Teams[TeamCounter].numberOfPlayers++;
        }else{
            printf("\nSpielereingabe Fehlgeschlagen!\n");
            sleep(2);
        }

    }while(askYesOrNo("\n\nMoechten Sie einen weiteren Spieler eingeben?") == EXIT_SUCCESS);

}

void deleteTeam() {
}

int createPlayer() {

    printf("\nErfassung der Spieler\n");
    printLine('=', 30);
    char * playerName = calloc(MAXNAMELENGTH, sizeof(char));      /*input Playername*/
    int playerArrayNum = Teams[TeamCounter].numberOfPlayers;

    printf("Geben Sie den Namen des Spielers ein!\n-> ");
    if(scanf("%s", playerName) > 0) {
                Teams[TeamCounter].player[playerArrayNum].name = playerName;
    }else{
        printf("Invalid input!\n");
        free(playerName);
        return EXIT_FAILURE;
    }

    printf("\nGeben Sie falls ggf. das Geburtsdatum des Spielers ein!\n"); /*input birthday*/
    char * input[10];
    scanf("%s", input);
    if(input[0] == '\n') {
        Teams[TeamCounter].player[playerArrayNum].birthday = NULL;
    }else{
        TDate * birthday = malloc(sizeof(TDate));
        if(getDateFromString(input, birthday) == EXIT_SUCCESS) {
            Teams[TeamCounter].player[playerArrayNum].birthday = birthday;
        }else{
            printf("\n\nEingabe/Geburtsdatum ungültig\n");
            free(birthday);
            return EXIT_FAILURE;
        }
    }

    int jerseyNr, scanErg;
    printf("\nGeben Sie die Trikotnummer des Spielers ein! ");
    scanErg = scanf("%d", jerseyNr);

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

void sortTeams() {
}

void listTeams() {
}
