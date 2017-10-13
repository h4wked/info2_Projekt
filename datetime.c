#include <stdio.h>
#include <stdlib.h>

#include "datetime.h"
#include "datastructure.h"

int isLeapYear (TDate * date) {

    /* alle 4 Jahre
     * alle 100 nicht
     * alle 400 Trotzdem
     * 1 ist schaltjahr
     * 0 ist nicht*/

    if ( (date->year % 400) == 0) return 1;

    if ( (date->year % 100) == 0) return 0;

    if ( (date->year % 4)   == 0) return 1;

    return 0;
}

int isDateValid (TDate * date) {

    // 1 valid 0 unvalid

    //Pruefung jahr
    if (date->year < 1) return 0;
    if (date->year > 2200) return 0;

    //Prüfung Monat
    if (date->month < 1) return 0;
    if (date->month > 12) return 0;

    //Prüfung Tag
    if (date->day < 1) return 0;

    //31 tage prüfen

    for(i=1; i<13; i+=2)
    {
        if (i==7) i--;
        if (i==date->month)
        {
            if (date->day<32)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }


    //auf 30 prüfen
    for(i=4; i<12; i+=2)
    {
        if (i==6) i++;
        if (i==date->month)
        {
            if (date->day<31)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    //auf Februar prüfen
    if (date->month==2)
    {
        if( isLeapYear(date) && (date->day==29) ) return 1;
        if( (date->day > 0) && (date->day < 29) ) return 0;
    }
    return 1;
}

int getDateFromString (char * string, TDate * date) {

    //Hilfsstring
    string *year = malloc(char*5)
    string *month = malloc(char*5)
    string *day = malloc(char*5)

    if( fscanf( string, "%s.%s.%s", day, month, year) < 3) {
        printf("ungültiges format!");
        return 0;
    }

    //Eintragen in date-struct
    date->day = atoi(day);
    date->month = atoi(month);
    date->year = atoi(year);
    
    if(isDateValid(date) == 1) return 1;

    printf("sollte nicht erreicht werden! getdatefromstring!");

    return 0;
}
