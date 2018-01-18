#ifndef SEARCH_H
#define SEARCH_H

int calcDivisionrest(char * string);

TListElement * search(THashTableElement * table, int (* compar)(TPlayer *, TPlayer *), TPlayer * player);

#endif // SEARCH_H
