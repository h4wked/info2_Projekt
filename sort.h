#ifndef SORT_H
#define SORT_H
#include "datastructure.h"

int sortTeam(int (* compar)(TPlayer *, TPlayer *));

void swap(TPlayer *a, TPlayer *b);

int quicksort(int (* compar)(TPlayer *, TPlayer *), TPlayer * links, TPlayer * rechts);

TPlayer * teile(int (* compar)(TPlayer *, TPlayer *), TPlayer * links, TPlayer * rechts);

int nameSort(TPlayer * a, TPlayer * b);

int birthSort(TPlayer * a, TPlayer * b);

int trikotSort(TPlayer * a, TPlayer * b);

int goalSort(TPlayer * a, TPlayer * b);

#endif SORT_H
