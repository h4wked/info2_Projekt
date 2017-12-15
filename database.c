#include "database.h"




void save(const char * url){
	FILE * file;
	if(!(file = fopen(url,"w"))){
		 	puts("Fehler beim schreiben der Datei: ");
		 	puts(url);
		 	return; // false
	}
	fputs("<Daten>\n",file);

	for( int i=0; i < TeamCounter;++i){
		saveTeam(&Teams[i],file);
	}

	fclose(file);
}

void saveTeam(TTeam * sav,FILE * out){
	fputs("\t<Team>\n",out);
	fputs("\t\t<Name>",out); fputs(sav->name, out ); fputs("</Name>\n",out);
	if(sav->coach != NULL) {
        fputs("\t\t<Trainer>",out); fputs(sav->coach, out ); fputs("</Trainer>\n",out);
	}
	for( int i = 0; i < sav->numberOfPlayers ; i++){
		savePlayer(&sav->player[i],out);
	}
	fputs("\t</Team>\n",out);
}
void savePlayer(TPlayer * player,FILE * fp){

    fprintf(fp, "\t<Player>\n", player->name);
    fprintf(fp, "\t\t<Name>%s</Name>\n", player->name);
    if(player->birthday != NULL) {
        fprintf(fp, "\t\t<Birthday>%d.%d.%d</Birthday>\n",
                player->birthday->Day,
                player->birthday->Month,
                player->birthday->Year);
    }
    fprintf(fp, "\t\t<TricotNr>%d</TricotNr>\n", player->nr);
    fprintf(fp, "\t\t<Goals>%d</Goals>\n", player->goals);
    fprintf(fp, " </Player>\n");
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
			TeamCounter++;
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

	if(!readLine(line,128,f)){
		free(line);
		return 0;
	}
	if(!strnncmp(line,"<Team>")){
		puts("reading Team!");
		(Teams + TeamCounter)->numberOfPlayers = 0;
		(Teams + TeamCounter)->name == NULL;
        (Teams + TeamCounter)->coach == NULL;

		char * buff = malloc(sizeof(char)*MAXNAMELENGTH);

		while(1) {

            memset(buff, '\0', sizeof(char)*MAXNAMELENGTH);
            if(!readLine(line,128,f)){
				free(line);
				return 0;
            }

            if((Teams+TeamCounter)->numberOfPlayers == MAXPLAYER){
                do{
                    readLine(line,128,f);
                }while(strnncmp(line,"</Team>"));
            }

            if(!strnncmp(line,"</Team>")){
                free(line);
                if(((Teams + TeamCounter)->name) == NULL) {
                    printf("Team has no name !\n");
                    sleep(1);
                    return 0;
                }
                return 1;
            }

            if(!strnncmp(line,"<Name>")){
                readTag(line,"Name",buff);
                char * data = calloc(strlen(buff), sizeof(char));
                strcpy(data, buff);
                (Teams + TeamCounter)->name = data;
                continue;

            }else if(!strnncmp(line,"<Trainer>")){
                readTag(line,"Trainer",buff);
                char * data = calloc(strlen(buff), sizeof(char));
                strcpy(data, buff);
                (Teams + TeamCounter)->coach = data;
                continue;

            }else if(!strnncmp(line,"<Player>")){
                int currentPlayer = (Teams+TeamCounter)->numberOfPlayers;
                TPlayer * player = (Teams + TeamCounter)  ->  player + currentPlayer;
                if(startPlayer(f, player)){
                    (Teams+TeamCounter)->numberOfPlayers++;
                }
                continue;

            }

            free(buff);
            free(line);
            printf("unexpected line! loading failed!\n");
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
    char * buff = malloc(sizeof(char)*MAXNAMELENGTH);
    while(1) {

        memset(buff, 0, strlen(buff));
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
            char * data = calloc(strlen(buff), sizeof(char));
            strcpy(data, buff);
            player->nr = atoi(data);
            free(data);
            continue;
        }else if(!strnncmp(line,"<Goals>")){
            readTag(line,"Goals",buff);
            char * data = calloc(strlen(buff), sizeof(char));
            strcpy(data, buff);
            player->goals = atoi(data);
            free(data);
            continue;
        }else if(!strnncmp(line,"<Birthday>")){
            readTag(line,"Birthday",buff);
            char * data = calloc(strlen(buff), sizeof(char));
            strcpy(data, buff);
            TDate * birthday = malloc(sizeof(TDate));
            getDateFromString(data, birthday);
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
		strncpy(buff/*+'\0'*/,&line[start],len-(start+end+1));
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
