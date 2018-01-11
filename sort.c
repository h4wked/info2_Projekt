#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "team.h"

int sortTeam(int (* compar)(TPlayer *, TPlayer *)) {

    TTeam * currentTeam = firstTeam;

    printf("Sortieren von %s .. ", currentTeam->name);
    int lastPlayer = currentTeam->numberOfPlayers - 1;
    quicksort( compar, &(currentTeam->player[0]) , &(currentTeam->player[lastPlayer]) );
    printf("erfolgreich!\n");
    while(currentTeam->nextTeam != NULL)
    {
        currentTeam = currentTeam->nextTeam;
        printf("Sortieren von %s .. ", Teams[c].name);
        lastPlayer = Teams[c].numberOfPlayers - 1;
        quicksort( compar, &(currentTeam->player[0]) , &(currentTeam.player[lastPlayer]) );
        printf("erfolgreich!\n");
    }
    printf("\nSortieren erfolgreich!\n");
}

void swap(TPlayer *a, TPlayer *b)
{
    TPlayer tmp = *a;
    *a = *b;
    *b = tmp;
}

int quicksort(int (* compar)(TPlayer *, TPlayer *), TPlayer * links, TPlayer * rechts) {

    if (links < rechts) {
         TPlayer * teiler = teile(compar, links, rechts);
         quicksort(compar, links, teiler-1);
         quicksort(compar, teiler+1, rechts);
    }
    return 0;
}

TPlayer * teile(int (* compar)(TPlayer *, TPlayer *), TPlayer * links, TPlayer * rechts)
{
    // pivot (Element to be placed at right position)
    TPlayer * pivot = rechts;

    TPlayer * i = (links - 1);  // Index of smaller element

    for (TPlayer * j = links; j <= rechts - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (/*arr[j] <= pivot*/ compar(j, pivot) < 1)
        {
            i++;    // increment index of smaller element
            //swap arr[i] and arr[j]
            swap(i, j);
        }
    }
    //swap arr[i + 1] and arr[high])
    swap(i+1, rechts);
    return (i + 1);
}

/*
TPlayer * teile(int (* compar)(TPlayer *, TPlayer *), TPlayer * links, TPlayer * rechts) {
     TPlayer * i = (links + 1);
     TPlayer * j = rechts;
     TPlayer *pivot = links;

     while (i < j) {
         // Suche von links ein Element, welches gleich oder größer als das Pivotelement ist
         while ( (compar(i, pivot) >= 0) && (i < j) ) {
             i++;
         }
         // Suche von rechts ein Element, welches kleiner als das Pivotelement ist
         while ( (compar(j, pivot) <= 0) && (j > i) ) {
             j--;
         }

         if (i < j) {
             //tausche daten[i] mit daten[j]
             swap(i, j);
         }

     } // solange i an j nicht vorbeigelaufen ist

     // Tausche Pivotelement (daten[rechts]) mit neuer endgültiger Position (daten[i])

     i--;
//     if (compar(i, &pivot) > 0) {
             //tausche daten[i] mit daten[rechts]
             swap(i, pivot);
     //}
     // gib die Position des Pivotelements zurück
     return i;
 }
*/

int nameSort(TPlayer * a, TPlayer * b){

    return strcmp(a->name, b->name);
}

int birthSort(TPlayer * a, TPlayer * b) {

    //Pruefung ob einer der Daten NULL ist
    if( (a->birthday == NULL) && (b->birthday == NULL) ) {
        return 0;
    }else if(a->birthday == NULL){
        return -1;
    }else if(b->birthday == NULL) {
        return 1;
    }

    //Pruefung Daten
    if(a->birthday->Year > b->birthday->Year){
        return 1;
    }else if(a->birthday->Year < b->birthday->Year){
        return -1;
    }

    if(a->birthday->Month > b->birthday->Month){
        return 1;
    }else if(a->birthday->Month < b->birthday->Month){
        return -1;
    }

    if(a->birthday->Day > b->birthday->Day){
        return 1;
    }else if(a->birthday->Day < b->birthday->Day){
        return -1;
    }
    return 0;

}

int trikotSort(TPlayer * a, TPlayer * b) {

    if(a->nr > b->nr) {
        return 1;
    }else if(a->nr < b->nr){
        return -1;
    }else{
        return 0;
    }
}

int goalSort(TPlayer * a, TPlayer * b) {

    if(a->goals < b->goals) {
        return 1;
    }else if(a->goals > b->goals) {
        return -1;
    }else{
        return 0;
    }

}



