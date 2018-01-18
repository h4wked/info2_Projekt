#ifndef LIST_H
#define LIST_H

#include "datastructure.h"

int insertInDVList(TTeam * newTeam);

void removeFromDVList(TTeam * team);

int compareTeamNames(TTeam * a, TTeam * b);

int appendInEVList(THashTableElement * tableElement, TTeam * team, TPlayer * player);

int removeFromEVList(THashTableElement * tableElement, TPlayer * player);

#endif // LIST_H
