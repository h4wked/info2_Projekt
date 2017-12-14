/*
 ============================================================================
 Name        : KalaHA.c
 Author      : Felix Spielmann
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 * Kleines Test-Programm...
 * läd teams.xml in das Array Teams
 * printed das gelesene
 * schreibt in die Datei teams2.xml
 *
 * mehr doku in database.h bzw database.c
 */



#include <stdio.h>
#include <stdlib.h>
#include "database.h"
TTeam Teams[8];
int TeamCounter = 0;
int main(void) {
	load("teams.xml",Teams);
	for (int i = 0; i < TeamCounter; i++) {
			TTeam t = Teams[i];

			printf("TEAM: %s\n\tTrainer: %s\n", t.name, t.coach);
			printf("%d Players:\n", t.numberOfPlayers);
			for (int j = 0; j < t.numberOfPlayers; j++) {
				TPlayer * p = &t.player[j];
				int d, m, y;
				TDate * date = p->birthday;
				d = date->Day;
				m = date->Month;
				y = date->Year;
				printf("\tPLAYER: %s\n\tNR: %d \n\tBDAY %d.%d.%d \n\tGOALS: %d\n\n",
						p->name, p->nr, d, m, y, p->goals);

			}
		}
	save("teams2.xml",Teams,2);

	return EXIT_SUCCESS;
}
