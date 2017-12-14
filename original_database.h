/*
 * database.h
 *
 *  Created on: 30.11.2017
 *      Author: schle_000
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "datastructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save(const char * url , TTeam teams[], size_t nrofteams); // Speichere alle teams in die Datei url
void saveTeam(TTeam * sav,FILE * out); // speichere Team sav in die Datei out
void savePlayer(TPlayer * sav,FILE * out); // speichere  Spieler sav in die Datei out

int load(const char * url); // lade Datei url


// ihr müsst hier noch irgendwas basteln, damit ihr das laden könnt, was das Programm ließt ;)
int startDaten(FILE * f); // Hilfsfunktion zum Parsen, Regel für <Daten>, ruft endDaten(...) auf
int endDaten(FILE * f); // </Daten>
int startTeam(FILE * f); // <Team>
int endTeam(FILE * f); // </Team>

// ließt Inhalt zwischen zwei Tags
// readTag("<Tag>Das ist ein Tag</Tag>","Tag",buffer) ==> buffer = "Das ist ein Tag" && return 1 bei erfolg oder 0 bei fehler
int readTag(char * line , const char * tag, char * buff );

void strtrim(char * buff_in, char * buff_out); // entfernt Leerzeichen und tabulatoren am Anfang einer Zeile
int readLine(char * buffer,int len, FILE * f); // ließt eine Zeile ein
#endif /* DATABASE_H_ */
