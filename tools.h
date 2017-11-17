#ifndef tools_h
	#define tools_h tools_h


	/******************************
	*   clearBuffer
	*   Löscht den Tastaturpuffer
	******************************/
	void clearBuffer();


	/******************************************************************************
	*   askAgain
	*   Fragt den Benutzer, ob das Programm noch einmal durchlaufen werden soll.
	*******************************************************************************/
	//int askAgain(int Row, int Col);
	void clearScreen();
	int askYesOrNo(char * phrase);
    void printLine(char c, int num);
    void waitForEnter();
    int getText(char * prompt, int allowedChars, int emptyAllowed, char ** target);

#endif
