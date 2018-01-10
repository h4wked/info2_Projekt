/************************************************************************************
*   In diesem Modul werden Funktionen, die in nahezu jedem Programm benötigt werden,
*   definiert.
************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "escapesequenzen.h"
#include "tools.h"


/******************************
*   clearBuffer
*   Löscht den Tastaturpuffer
******************************/
void clearBuffer()
{
	char Dummy = 'a';			//Variable, die den Tastaturpuffer auslesen soll
	do					//Puffer soll ausgelesen werden
	{
		scanf("%c" , &Dummy);
	} while (Dummy != '\n');			//bis das Zeichen 'Eingabetaste' eingelesen wurde
}



/******************************************************************************
*   askAgain
*   Fragt den Benutzer, ob das Programm noch einmal durchlaufen werden soll.
*******************************************************************************/
/*int askAgain(int Row, int Col)
{
	int KorrekteEingabe;			//Variable, die kennzeichnet, ob der Benutzer eine korrekte Eingabe gemacht hat
	char Answear;				//Variable, die als Wert die Antwort des Beunutzers hat
	POSITION(Row, Col);	printf("Moechten Sie noch einmal? (J|N)");	//an der entsprechenden Position wird die Aufforderung an den
										//Benutzer ausgegeben
	POSITION(++Row, Col);	KorrekteEingabe = scanf("%c" , &Answear);	//eine Zeile darunter wird die Antwort des Benutzers eingelesen
										//und mittels 'KorrekteEingabe' auf Richtigkeit in Bezug
										//auf Datentyp geprüft
	if (Answear != '\n')
	{
		clearBuffer();			//Tastatur-Puffer löschen, wenn der Benutzer nicht 'Eingabetaste' eingegeben hat
	}

	//Wenn der Benutzer keine der benötigten Antworten eingibt
	if ( (Answear != 'J') && (Answear != 'j') && (Answear != 'N') && (Answear != 'n') && (Answear != 'Y') && (Answear != 'y') )
	{
		KorrekteEingabe = 0;		//dann wird seine Eingabe als nicht richtig gekennzeichnet
	}

	//solange der Benutzer keine richtige Eingabe macht
	while (!KorrekteEingabe)
	{
		POSITION(Row, Col);	CLEAR_LINE;			//falsche Eingabe des Benutzers an der richtigen Position löschen
		POSITION(Row, Col);	printf("Fehler: Sie muessen 'J' oder 'N' eingeben!");	//an der gleichen Position Fehlermeldung ausgeben
		POSITION(++Row, Col);	KorrekteEingabe = scanf("%c" , &Answear);	//eine Zeile darunter wird nochmal eine Eingabe des Benutzers
											//eingelesen und mittels 'KorrekteEingabe' auf Richtigkeit in Bezug
											//auf Datentyp geprüft
		if (Answear != '\n')
		{
			clearBuffer();			//Tastatur-Puffer löschen, wenn der Benutzer nicht 'Eingabetaste' eingegeben hat
		}

		//Eingabe des Benutzers als ungültig kennzeichnen, wenn er keine der benötigten Antworten gegeben hat
		if ( (Answear != 'J') && (Answear != 'j') && (Answear != 'N') && (Answear != 'n') && (Answear != 'Y') && (Answear != 'y') )
        	{
                	KorrekteEingabe = 0;
        	}
	}
	//etwaige Fehlermeldung an den Benutzer und seine Eingabe wird gelöscht
	POSITION(Row, Col);     CLEAR_LINE;
	POSITION(++Row, Col);     CLEAR_LINE;

	//Je nach Antwort des Benutzers gibt die Funktion einen Wahrheitswert 1 (wahr) oder 0 (falsch) zurück
	if ( (Answear == 'J') || (Answear == 'j') || (Answear == 'Y') || (Answear == 'y') )
	{
		return 1;		//Benutzer möchte noch einmal
	}
	else if ( (Answear == 'N') || (Answear == 'n') )
	{
		return 0;		//Benutzer möchte das Programm beenden
	}
	else
	{
		POSITION(Row, Col);     printf("Unwahrscheinlicher Fehler eingetreten");	//Programm wird beendet, falls durch höhere Gewalt
		return 0;									//in der Variablen 'Answear' kein gültiger Wert
	}											//gespeichert ist

	return 0;
}*/


//FUnktioniert nur für Windows

void clearScreen() {

    system("clear");
    //system("cls");
}

int askYesOrNo(char * phrase) {

    char Answear;
    do{
        printf("%s\n",phrase);
        scanf("%c",&Answear);
        if (Answear != '\n')
            clearBuffer();
        if ( (Answear == 'J') || (Answear == 'j') || (Answear == 'Y') || (Answear == 'y') )
        {
		return EXIT_SUCCESS;		//Benutzer möchte noch einmal
        }
        else if ( (Answear == 'N') || (Answear == 'n') )
        {
            return EXIT_FAILURE;		//Benutzer möchte das Programm beenden
        }
    }while(1);
}

void printLine(char c, int num) {
    for(int i = 0; i<num; i++) {
        printf("%c", c);
    }
    printf("\n");
}

void waitForEnter() {
    printf("\nBitte Eingabetaste drücken!\n");
    char enter = 0;
    clearBuffer();
    //while( getchar() != '\n' );
}

int getText(char * prompt, int allowedChars, int emptyAllowed, char ** target) {

    printf("%s", prompt);

    char * input = calloc(allowedChars, sizeof(prompt));
    int scanErg;

    if(scanErg = scanf("%39[^\n]", input) > 0) {

        clearBuffer();
        int strLen = strlen(input);
        *target = calloc(strLen+1, sizeof(char));

        strcpy(*target, input);

        free(input);
        return EXIT_SUCCESS;

    }else if(emptyAllowed) {

        clearBuffer();
        *target = NULL;
        free(input);
        return EXIT_SUCCESS;

    }else{

        clearBuffer();
        printf("Invalid input!\n");
        free(input);
        return EXIT_FAILURE;

    }
}
