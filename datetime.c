#include <stdio.h>
#include <stdlib.h>

#include "datetime.h"

#include "datastructure.h"
#include "tools.h"

int isLeapYear (TDate * date) {

    /* alle 4 Jahre
     * alle 100 nicht
     * alle 400 Trotzdem
     * 1 ist schaltjahr
     * 0 ist nicht*/

    if ( (date->Year % 400) == 0) return 1;

    if ( (date->Year % 100) == 0) return 0;

    if ( (date->Year % 4)   == 0) return 1;

    return 0;
}

int isDateValid (TDate * date) {

    // 1 valid 0 unvalid

    //Pruefung jahr
    if (date->Year < 1) return 0;
    if (date->Year > 2200) return 0;

    //Prüfung Monat
    if (date->Month < 1) return 0;
    if (date->Month > 12) return 0;

    //Prüfung Tag
    if (date->Day < 1) return 0;

    //31 tage prüfen

    int i=0;

    for(i=1; i<13; i+=2)
    {
        if (i==7) i--;
        if (i==date->Month)
        {
            if (date->Day<32)
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
        if (i==date->Month)
        {
            if (date->Day<31)
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
    if (date->Month==2)
    {
        if( isLeapYear(date) && (date->Day == 29) ) return 1;
        if( (date->Day > 0) && (date->Day < 29) ) return 1;
    }
    return 0;
}


int getDateFromString (char * input, TDate * date)
{

    if(sscanf(input, "%d.%d.%d", &(date->Day), &(date->Month), &(date->Year)) < 3) {
        date = NULL;
        printf("Ungueltiges Format!\n\n");
        return EXIT_FAILURE;
    }

    if(isDateValid(date) == 1) return EXIT_SUCCESS;
    printf("Datum ungueltig!\n\n");

    return EXIT_FAILURE;
}

int isTimeValid (TTime * time) {

    // 1 valid 0 unvalid

    //Pruefung stunden
    if (time->Hour >=  24) return 0;
    if (time->Hour < 0 ) return 0;

    //Prüfung Minuteuten
    if (time->Minute >=  60) return 0;
    if (time->Minute < 0 ) return 0;

    //Prüfung sekunden
    if (time->Second >= 60) return 0;
    if (time->Second < 0 ) return 0;

    return 1;
}

int getTimeFromString (char * string, TTime * time){

    //Hilfsstring
    char * Hour = malloc(sizeof(char)*5);
    char * Minute = malloc(sizeof(char)*5);
    char * Second = malloc(sizeof(char)*5);

    int i;
    if( (i = sscanf( string, "%2s:%2s:%2s", Hour, Minute, Second)) < 3) {
            printf("ungueltiges Format!\n");
        return 0;
    }

    //Eintragen in time-struct
    time->Hour = atoi(Hour);
    time->Minute = atoi(Minute);
    time->Second = atoi(Second);

    if(isTimeValid(time) == 1) return 1;


    return 0;
}

int getDate(char * question, int numPlayer, TTeam * team) {

    int scanErg;
    printf("%s",question);
    char input[10];
    scanErg = scanf("%39[^\n]", input);
    if(scanErg == 0) {
        team->player[numPlayer].birthday = NULL;
        return EXIT_SUCCESS;
    }else{
        TDate * birthday = malloc(sizeof(TDate));
        if(getDateFromString(input, birthday) == EXIT_SUCCESS) {
            team->player[numPlayer].birthday = birthday;
            return EXIT_SUCCESS;
        }else{
            clearBuffer();
            free(birthday);
            return EXIT_FAILURE;
        }
    }
}

void printDate(TDate * date) {

    printf("%d.%d.%d", date->Day, date->Month, date->Year);
}
