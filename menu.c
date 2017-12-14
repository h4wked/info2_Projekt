#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "database.h"
#include "tools.h"

int getMenu(char * menuTitle, char * menuPoints[], int numberOfPoints) {

    int choice = 0;
    int scanErg;

    while(choice == 0) {

        clearScreen();                                              /*Ausgabe des Menus*/
        printf("%s\n",menuTitle);
        printLine('-', 30);

        for(int c = 0; c < numberOfPoints; c++) {                   /*Ausgabe der Menupunkte*/
                if((printf("%s\n",menuPoints[c])) == 0) break;
        }

        printf("\nIhre Wahl: ");                                    /*Benutzereingabe*/
        scanErg = scanf("%d", &choice);
        clearBuffer();

        if (scanErg == 0){
                printf("ungueltige Eingabe!\n");
                sleep(1);
                continue;
        }
        if(choice > numberOfPoints || choice < 0) {
            printf("ungueltige Eingabe!\n");
            sleep(1);
            choice = 0;
            continue;
        }
    }
    return choice;
}
