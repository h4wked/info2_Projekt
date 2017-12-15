#ifndef SORT_H
#define SORT_H
#include "datastructure.h"

int teamQSort(int (*compar)(TPlayer, TPlayer));

int nameSort(TPlayer a, TPlayer b);

int birthSort(TPlayer a, TPlayer b);

int trikotSort(TPlayer a, TPlayer b);

int goalSort(TPlayer a, TPlayer b);

#endif SORT_H
