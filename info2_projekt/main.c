#include <stdio.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"

void inputDate();
void inputTime();

int main()
{
   do
   {
      clearScreen();
      printf("Hinweis: Druecken Sie nur die Eingabetaste,\n");
      printf("         um die jeweilige Eingabe abzubrechen.\n\n");

      inputDate();
      inputTime();
   } while ( 0 /*askYesOrNo("Moechten Sie noch einmal (j/n) ? ")*/);   //TODO!!!!

   return 0;
}

/********************************************************************
 * Funktion void inputDate(void)
 *   - Benutzer soll ein Datum eingeben.
 *   - Eingabe wird mit Hilfe der Funktion getDateFromString geparst
 *     und geprueft. Bei gueltigem Datum steht dieses in der Datums-
 *     variable Date.
 *   - Ergebnis der Eingabe wird entsprechend angezeigt.
 *   - wird nur die Eingabetaste gedrueckt, wird die Funktion ohne
 *     weitere Bildschirmausgabe beendet.
 * Paramater: keine
 * Funktionsergebnis: nichts
 *******************************************************************/
void inputDate()
{
   TDate Date;
   char Input[20];
   int ok = 0;

   do
   {
      printf("Geben Sie bitte ein gueltiges Datum ein: ");
      *Input = '\0';
      scanf("%19[^\n]", Input);
      clearBuffer();
      if (*Input)
         if (getDateFromString(Input, &Date))
         {
            printf("Das Datum %02i.%02i.%04i ist gueltig!\n", Date.Day, Date.Month, Date.Year);
            ok = 1;
         }
         else
            printf("Das eingegebene Datum %s ist ungueltig!\n", Input);
      else
         break;
   } while (!ok);

   printf("\n");
}

/********************************************************************
 * Funktion void inputTime(void)
 *   - Benutzer soll eine Uhrzeit eingeben.
 *   - Eingabe wird mit Hilfe der Funktion getTimeFromString geparst
 *     und geprueft. Bei gueltiger Uhrzeit steht diese in der
 *     Uhrzeitvariable Time.
 *   - Ergebnis der Eingabe wird entsprechend angezeigt.
 *   - wird nur die Eingabetaste gedrueckt, wird die Funktion ohne
 *     weitere Bildschirmausgabe beendet.
 * Paramater: keine
 * Funktionsergebnis: nichts
 *******************************************************************/
void inputTime()
{
   TTime Time;
   char Input[20];
   int ok = 0;

   do
   {
      printf("Geben Sie bitte eine gueltige Uhrzeit ein: ");
      *Input = '\0';
      scanf("%19[^\n]", Input);
      clearBuffer();
      if (*Input)
         if (getTimeFromString(Input, &Time))
         {
            printf("Die Uhrzeit %02i:%02i:%02i ist gueltig!\n", Time.Hour, Time.Minute, Time.Second);
            ok = 1;
         }
         else
            printf("Die eingegebene Uhrzeit %s ist ungueltig!\n", Input);
      else
         break;
   } while (!ok);

   printf("\n");
}
