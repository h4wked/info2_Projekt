#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

int getMenu(char * menutitle, char * menupoints[], int numberOfPoints) {

    int choice = 0;

    while(choice == 0) {

        clearScreen();                                              /*Ausgabe des Menus*/
        printf("%s\n",menutitle);
        printLine('-', 30);

        for(int c = 0; c < numberOfPoints; c++) {                   /*Ausgabe der Menupunkte*/
                if((printf("%s\n",menupoints[c])) == 0) break;
        }

        printf("\nIhre Wahl: ");                                    /*Benutzereingabe*/
        scanf("%d", &choice);
        if(choice > numberOfPoints || choice < 0) {
            printf("ungueltige Eingabe!\n");
            sleep(1);
            choice = 0;
            continue;
        }
    }
}
