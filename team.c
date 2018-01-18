#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "team.h"

#include "datastructure.h"
#include "sort.h"
#include "tools.h"
#include "datetime.h"
#include "menu.h"
#include "search.h"

THashTableElement PlayerIndex[MAXINDEX];

/* TeamCounter und Teams[n].numberOfPlayers entprechen der physischen Anzahl an Spielern!! */

int createTeam() {

    clearScreen();
    printf("Erfassung einer neuen Mannschaft\n");
    printLine('=', 30);
    TTeam * newTeam = malloc(sizeof(TTeam));

    newTeam->numberOfPlayers = 0;
    newTeam->nextTeam = NULL;
    newTeam->prevTeam = NULL;

    if(getText("\nGeben Sie den Namen der Mannschaft ein!\n-> ", MAXNAMELENGTH, 0, &(newTeam->name)) == EXIT_SUCCESS)
    {
    }else{
        memset(newTeam, 0, sizeof(TTeam));
        return EXIT_FAILURE;
    }

    if(getText("Geben Sie den Namen des Trainers ein!\n-> ", MAXNAMELENGTH, 1, &(newTeam->coach)) == EXIT_SUCCESS) {
    }else{
        oneTeamCleanup(newTeam);
        memset(newTeam, 0, sizeof(TTeam));
        return EXIT_FAILURE;
    }


    do {
        if(createPlayer(newTeam) == EXIT_SUCCESS) {
            newTeam->numberOfPlayers++;
        }else{
            printf("\nSpielereingabe Fehlgeschlagen!\n");
            sleep(1);
        }

    }while(askYesOrNo("\n\nMoechten Sie einen weiteren Spieler eingeben? (j/n)") == EXIT_SUCCESS);

    insertInDVList(newTeam);
    return EXIT_SUCCESS;

}

int deleteTeam() {

    TTeam * currentTeam = firstTeam;
    int counter = 0;

    clearScreen();
    printf("Liste der Mannschaften\n");
    printLine('=', 24);
    if(firstTeam == NULL)
    {
        printf("Keine Teams vorhanden!\n");
        waitForEnter();
        return EXIT_SUCCESS;
    }
    printf("%d: %s\n", counter+1, currentTeam->name);
    do
    {
        currentTeam = currentTeam->nextTeam;
        counter++;
        printf("%d: %s\n", counter+1, currentTeam->name);
    }while(currentTeam->nextTeam != NULL);

    printf("\nWelche Manschaft moechten Sie loeschen? (0 fuer abbruch) ");
    int erg = scanf("%d", &counter);
    if(erg < 1)
    {
        printf("\nFehlerhafte Eingabe, kehre zum Hauptmenu zurück");
        return EXIT_FAILURE;
    }
    else if(counter == 0)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        currentTeam = firstTeam;
        for(int c = 1; c < counter; c++)
        {
            currentTeam = currentTeam->nextTeam;
        }
        removeFromDVList(currentTeam);
        oneTeamCleanup(currentTeam);
        return EXIT_SUCCESS;
    }
}

int createPlayer(TTeam * newTeam) {

    int scanErg;
    printf("\nErfassung eines Spielers\n");
    printLine('=', 30);
    if(newTeam->numberOfPlayers >= MAXPLAYER){
        printf("Team hat maximale Anzahl an Spielern!\n");
        sleep(1);
        return EXIT_FAILURE;
    }
    int playerArrayNum = newTeam->numberOfPlayers;

    if((getText("Geben Sie den Namen des Spielers ein!\n-> ", MAXNAMELENGTH, 0, &(newTeam->player[playerArrayNum].name))) == EXIT_FAILURE) {
       return EXIT_FAILURE;
       }         //Playername
    do{
    if(getDate("\nGeben Sie ggf. das Geburtsdatum des Spielers ein!\n", playerArrayNum, newTeam) == EXIT_SUCCESS) break;                                                 //Birthday
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
        newTeam->player[playerArrayNum].nr = jerseyNr;
    }
    newTeam->player[playerArrayNum].goals = 0;  //Tore Null setzten

    //Anlegen des Hash-Eintrages
    int hash = calcDivisionrest(newTeam->player->name);
    appendInEVList(PlayerIndex[hash], newTeam, newTeam->player[playerArrayNum]);

    return EXIT_SUCCESS;


}

void deletePlayer(TTeam * team)
{
    clearScreen();
    printf("Waehlen Sie den Spieler aus der gelöscht werden soll.\n\n");
    for(int c = 0; c < team->numberOfPlayers; c++)
    {
        printf("%d: ", c+1);
        listOnePlayer(&(team->player[c]));
    }
    printf("\nIhre Wahl: ");
    int chosenPlayer;
    scanf("%d", &chosenPlayer);
    chosenPlayer--;
    //Entfernen aus Hash-Table
    int hash = calcDivisionrest(team->player[chosenPlayer].name);
    removeFromEVList(PlayerIndex[hash], team->player[chosenPlayer]);

    //freigeben des allocierten speichers
    free(team->player[chosenPlayer].name);                         //Freigeben speicher zu löschender Spieler
    free(team->player[chosenPlayer].birthday);

    team->numberOfPlayers --;                                       //reduziere spieleranzahl im Team

    if(chosenPlayer != (team->numberOfPlayers-1) )
    {
        team->player[chosenPlayer].name = team->player[team->numberOfPlayers].name;   //setze letzten spieler in das arrayfeld des geloeschten ein
        team->player[chosenPlayer].birthday = team->player[team->numberOfPlayers].birthday;
        team->player[chosenPlayer].goals = team->player[team->numberOfPlayers].goals;
        team->player[chosenPlayer].nr = team->player[team->numberOfPlayers].nr;
    }
    memset(&team->player[team->numberOfPlayers], 0, sizeof(TPlayer));        //lösche letzen spieler
    clearBuffer();
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


int listTeams() {
    clearScreen();
    if(firstTeam == NULL) {
        printf("Keine Mannschaften vorhanden!\n");
        return EXIT_SUCCESS;
    }

    char * menu[] =
    {
        "Aufwarts ausgeben",
        "Abwaerts ausgeben",
        "zurueck zum Hauptmenue"
    };
    int choice = getMenu("Auswahl der Ausgabemethode", menu, 3);

    if (choice == 3)
    {
       return EXIT_SUCCESS;
    }
    else if(choice == 1)
    {
        TTeam * currentTeam = firstTeam;
        printf("Liste der Mannschaften\n");
        printLine('=', 30);
        listOneTeam(currentTeam);
        while(currentTeam->nextTeam != NULL)
        {
            currentTeam = currentTeam->nextTeam;
            listOneTeam(currentTeam);
        }
    }
    else if(choice == 2)
    {
        TTeam * currentTeam = lastTeam;
        printf("Liste der Mannschaften\n");
        printLine('=', 30);
        listOneTeam(currentTeam);
        while(currentTeam->prevTeam != NULL)
        {
            currentTeam = currentTeam->prevTeam;
            listOneTeam(currentTeam);
        }
    }

}

void listOneTeam(TTeam * team) {
    printf("\nName:           : %s\n",team->name);

    if(team->coach != NULL) {
        printf("Trainer         : %s\n",team->coach);
    }

    printf("Anzahl Spieler  : %d\n", team->numberOfPlayers);

    printf("Spieler:\n");
    for(int c = 0; c < team->numberOfPlayers; c++) {
        printf("\t%2d: ",c+1);
        listOnePlayer(&(team->player[c]));
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

/*
void swapPlayers(TPlayer * a, TPlayer * b)
{
    TPlayer temp;
    temp.name = a->name;
    temp.birthday = a->birthday;
    temp.goals = a->goals;
    temp.nr = a->nr;

    a->name = b->name;
    a->birthday = b->birthday;
    a->goals = b->goals;
    a->nr = b->nr;

    b->name = temp.name;
    b->birthday = temp.birthday;
    b->goals = temp.goals;
    b->nr = temp.nr;
}
*/

TTeam * choseTeam()
{
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
    if(chosenTeam == 0) return NULL;
    clearBuffer();
    return currentTeam;
}

void teamCleanup()
{
    TTeam * currentTeam = firstTeam;

    oneTeamCleanup(currentTeam);
    while(currentTeam->nextTeam != NULL)
    {
        currentTeam = currentTeam->nextTeam;
        oneTeamCleanup(currentTeam);
    }
}

void oneTeamCleanup(TTeam * team)
{
    free(team->name);
    if(team->coach != NULL) {
        free(team->coach);
    }
    for(int c = 0; c < team->numberOfPlayers; c++) {
        free(team->player[c].name);
        if(team->player[c].birthday != NULL) {
            free(team->player[c].birthday);
        }
    }
}
