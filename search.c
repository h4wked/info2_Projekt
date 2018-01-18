#include <stdio.h>
#include <stdlib.h>

#include "datastructure.h"
#include "search.h"

int calcDivisionrest(char * string)
{
    int len = strlen(string);
    char * pointer = string;
    int result = 0;

    for(int c = 0; c < len; c++)
    {
        result += * pointer;
        pointer ++;
    }

    result %= MAXINDEX;
    return result;
}

TListElement * search(THashTableElement * table, int (* compar)(TPlayer *, TPlayer *), TPlayer * player)
{
    int hash = calcDivisionrest(player->name);
    if(table[hash].first == NULL)
        return NULL;
    TListElement * element = table[hash].first;
    while(compar(player, element->Player) != 0)
    {
        if(element->next == NULL)
            return NULL;
        element = element->next;
    }
    return element;
}
