#include <stdlib.h>
#include <stdio.h>

int getMenu(char * menutitle, char * menupoints[], int numberOfPoints) {

    int choice = 0;

    while(choice == 0) {

        clearScreen();                  /*Ausgabe des Menus*/
        printf("%s\n",menutitle);
        printline('-', 30);
        for(int c; c = 0; c < numberOfPoints) {
                if((printf("%s\n",menupoints[c])) == 0) break;
        }
        printf("\nIhre Wahl: ");
        scanf("%d", choice);
    }
}
