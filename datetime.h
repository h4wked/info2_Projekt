#ifndef DATETIME_H
#define DATETIME_H

#include "datastructure.h"

int isLeapYear (TDate * date);

int isDateValid (TDate * date);

int getDateFromString (char * string, TDate * date);

int isTimeValid (TTime * time);

int getTimeFromString (char * string, TTime * time);

int getDate(char * question, int numPlayer, TTeam * team);

void printDate(TDate * date);

#endif
