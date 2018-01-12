#include "database.h"
#include "list.h"



void save(const char * url){
	FILE * file;
	if(!(file = fopen(url,"w"))){
		 	puts("Fehler beim schreiben der Datei: ");
		 	puts(url);
		 	return; // false
	}
	fputs("<Daten>\n",file);

	//for( int i=0; i < TeamCounter;++i){
    TTeam * currentTeam = firstTeam;
    saveTeam(currentTeam, file);
    while(currentTeam->nextTeam != NULL)
    {
		saveTeam(currentTeam, file);
	}
	fputs("</Daten>\n",file);
	fclose(file);
}

void saveTeam(TTeam * sav,FILE * out){
	fputs("<Team>\n",out);
	fputs(" <Name>",out); fputs(sav->name, out ); fputs("</Name>\n\0",out);
	if(sav->coach != NULL) {
        fputs(" <Trainer>",out); fputs(sav->coach, out ); fputs("</Trainer>\n",out);
	}
	for( int i = 0; i < sav->numberOfPlayers ; i++){
		savePlayer(&sav->player[i],out);
	}
	fputs("</Team>\n",out);
}
void savePlayer(TPlayer * player,FILE * fp){

    fprintf(fp, "<Player>\n", player->name);
    fprintf(fp, " <Name>%s</Name>\n", player->name);
    if(player->birthday != NULL) {
        fprintf(fp, " <Birthday>%02d.%02d.%04d</Birthday>\n",
                player->birthday->Day,
                player->birthday->Month,
                player->birthday->Year);
    }
    fprintf(fp, " <TricotNr>%d</TricotNr>\n", player->nr);
    fprintf(fp, " <Goals>%d</Goals>\n", player->goals);
    fprintf(fp, "</Player>\n");
    }

int load(const char * url){

	 FILE * file;
	 if(!(file = fopen(url,"r"))){
		 	puts("Fehler beim Lesen der Datei: ");
		 	puts(url);
		 	return 0; // false
	 }

	 if(startDaten(file)){
		 puts("erfolgreich geparst!");
	 }else{
		 puts("Fehler beim Lesen!");
	 }

	 pclose(file);

	 return 1; // true/success
}

int startDaten(FILE * f){
	char *  line = (char*)calloc(128,sizeof(char));
	if(!readLine(line,128,f)){
		free(line);
		return 0;
	}
	if(!strnncmp(line,"<Daten>")){
		puts("reading team!");
		while(startTeam(f)){
			puts("reading next team!");
		}
		free(line);
		return endDaten(f);
	}
	free(line);
	return 0;
}

int endDaten(FILE * f){
	char *  line = (char*)calloc(128,sizeof(char));
		if(!readLine(line,128,f)){
			free(line);
			return 0;
		}
		if(!strnncmp(line,"</Daten>")){
			free(line);
			return 1;
		}
		free(line);
		return 0;
}
int startTeam(FILE * f){
	char *  line = (char*)calloc(128,sizeof(char));
    TTeam * newTeam = malloc(sizeof(TTeam));

	if(!readLine(line,128,f)){
		free(line);
		return 0;
	}
	if(!strnncmp(line,"<Team>")){
		puts("reading Team!");
		newTeam->numberOfPlayers = 0;
		newTeam->name = NULL;
        newTeam->coach = NULL;
        newTeam->nextTeam = NULL;
        newTeam->prevTeam = NULL;

		char * buff = malloc(sizeof(char)*MAXNAMELENGTH);

		while(1) {

            memset(buff, '\0', sizeof(char)*MAXNAMELENGTH);
            if(!readLine(line,128,f)){
				free(line);
				return 0;
            }

            if(!strnncmp(line,"</Team>")){
                free(line);
                if((newTeam->name) == NULL) {
                    printf("Team has no name !\n");
                    sleep(1);
                    return 0;
                }
                insertInDVList(newTeam);                //LADEN ERFOLGREICH! TEAM WIRD EINGEFÜGT
                return 1;
            }

            if(newTeam->numberOfPlayers == MAXPLAYER){
                do{
                    readLine(line,128,f);
                }while(strnncmp(line,"</Team>"));
                free(line);
                return 1;
            }


            if(!strnncmp(line,"<Name>")){
                readTag(line,"Name",buff);
                char * data = calloc(strlen(buff), sizeof(char));
                strcpy(data, buff);
                newTeam->name = data;
                continue;

            }else if(!strnncmp(line,"<Trainer>")){
                readTag(line,"Trainer",buff);
                char * data = calloc(strlen(buff), sizeof(char));
                strcpy(data, buff);
                newTeam->coach = data;
                continue;

            }else if(!strnncmp(line,"<Player>")){
                int currentPlayer = newTeam->numberOfPlayers;
                TPlayer * player = newTeam  ->  player + currentPlayer;
                if(startPlayer(f, player)){
                    newTeam->numberOfPlayers++;
                }
                continue;

            }

            free(buff);
            free(line);
            printf("unexpected line! loading failed!\n");
            oneTeamCleanup(newTeam);
            free(newTeam);                                      //LADEN SCHLUG FEHL!TEAM WIRD GELÖSCHT
            sleep(1);
            return 0;
        }
	}
	free(line);
	return 0;
}

int startPlayer(FILE * f, TPlayer * player) {

    char * line = (char*)calloc(128,sizeof(char));
    player->name = NULL;
    player->nr = 0;
    player->goals = 0;
    player->birthday = NULL;
    char * buff = calloc(MAXNAMELENGTH+1, sizeof(char));
    while(1) {

        memset(buff, 0, MAXNAMELENGTH+1);
        if(!readLine(line,128,f)){
            free(line);
            return 0;
        }

        if(!strnncmp(line,"</Player>")){
            free(line);
            if( (player->name == NULL) || player->nr == 0) {
                printf("Player has no name/tricotnr !\n");
                sleep(1);
                return 0;
            }
            return 1;
        }



        if(!strnncmp(line,"<Name>")){
            readTag(line,"Name",buff);
            char * data = calloc(strlen(buff), sizeof(char));
            strcpy(data, buff);
            player->name = data;
            continue;
        }else if(!strnncmp(line,"<TricotNr>")){
            readTag(line,"TricotNr",buff);
            player->nr = atoi(buff);
            continue;
        }else if(!strnncmp(line,"<Goals>")){
            readTag(line,"Goals",buff);
            player->goals = atoi(buff);
            continue;
        }else if(!strnncmp(line,"<Birthday>")){
            readTag(line,"Birthday",buff);
            TDate * birthday = malloc(sizeof(TDate));
            getDateFromString(buff, birthday);
            player->birthday = birthday;
            continue;
        }else{
            printf("unexpected line! loading failed!\n");
            free(buff);
            return 0;
        }
    }
    free(buff);
    return 1;
}
/*int endTeam(FILE * f){
	char *  line = (char*)calloc(128,sizeof(char));
	if(!readLine(line,128,f)){
		free(line);
		return 0;
	}
	if(!strnncmp(line,"</Team>")){
		free(line);
		return 1;
		}
	free(line);
	return 0;
}*/

int readTag(char * line , const char * tag, char * buff ){
	char * endtag = (char*) calloc(strlen(tag)+3,sizeof(char));
	char * starttag = (char*) calloc(strlen(tag)+2,sizeof(char));
	sprintf(endtag,"</%s>",tag);
	sprintf(starttag,"<%s>",tag);

	if(!strnncmp(line,starttag) && strstr(line,endtag)){
		size_t start = strlen(starttag);
		size_t end = strlen(endtag);
		size_t len = strlen(line);

		strncpy(buff,&line[start],len-(start+end));
		return 1;
	}
	free(endtag);

	return 0;
}


void strtrim(char * buff_in, char * buff_out){
	size_t len = strlen(buff_in);
	buff_in[len-1]='\0';
	int start=0;
	for ( start = 0; start < len; ++start) {
		if((buff_in[start]!= ' ') && (buff_in[start]!='\t')){
			break;
		}
	}

	strncpy(buff_out,&buff_in[start],(len-start));

    start = 0;
    while (*(buff_out + start) != '\0')
    {
        if (*(buff_out + start) == '\r')
        {
            *(buff_out + start) = '\0';
            break;
        }
        start++;
    }
}
int strnncmp(char * str, const char * str2){
	size_t l = strlen(str2);
	return strncmp(str,str2,l);
}
int readLine(char * buffer,int len, FILE * f){
	char *  buf = (char*)calloc(128,sizeof(char));
	if(fgets(buf,128,f)){
		strtrim(buf,buffer);
		free(buf);
		return 1;
	}
	free(buf);
	return 0;
}
