#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

/*
int sortTeam() {

   int *ptr1 = links;
   int *ptr2 = rechts;
   int w, x;

   x = *(links + (rechts - links >> 1));
   do {
      while(*ptr1 < x) ptr1++;
      while(*ptr2 > x) ptr2--;
      if(ptr1 > ptr2)
         break;
      w = *ptr1;
      *ptr1 = *ptr2;
      *ptr2 = w;
   }while(++ptr1 <= --ptr2);
   if(links < ptr2)  sortTeam(links, ptr2);
   if(ptr1 < rechts) sortTeam(ptr1, rechts);
}
*/

int teamQSort(int (*compar)(TPlayer, TPlayer)) {

}

int nameSort(TPlayer a, TPlayer b){

}

int birthSort(TPlayer a, TPlayer b) {

}

int trikotSort(TPlayer a, TPlayer b) {

}

int goalSort(TPlayer a, TPlayer b) {

}
