#include "database.h"




void save(const char * url , TTeam teams[], size_t nrofteams){
	FILE * file;
	if(!(file = fopen(url,"w"))){
		 	puts("Fehler beim schreiben der Datei: ");
		 	puts(url);
		 	return; // false
	}
	fputs("<Daten>\n",file);

	for( int i=0; i < nrofteams;++i){
		saveTeam(&teams[i],file);
	}

	fclose(file);
}

void saveTeam(TTeam * sav,FILE * out){
	fputs("\t<Team>\n",out);
	fputs("\t\t<Name>",out); fputs(sav->name, out ); fputs("</Name>\n",out);
	fputs("\t\t<Trainer>",out); fputs(sav->coach, out ); fputs("</Trainer>\n",out);

	for( int i = 0; i < sav->numberOfPlayers ; i++){
		savePlayer(&sav->player[i],out);
	}
	fputs("\t</Team>\n",out);
}
void savePlayer(TPlayer * sav,FILE * out){}

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
	if(!readLine(line,128,f)){
		free(line);
		return 0;
	}
	if(!strnncmp(line,"<Team>")){
		puts("reading Team!");
		if(!readLine(line,128,f)){
				free(line);
				return 0;
		}
		if(!strnncmp(line,"<Name>")){
			//readTag(line,"Name",buff)
		}else if(!strnncmp(line,"<Trainer>")){
			//readTag(line,"Name",buff)
		}else if(!strnncmp(line,"<Player>")){
			// while(startPlayer(f)){ ... }

		}

		//free(buff);
		free(line);
		return endTeam(f);
	}
	free(line);
	return 0;
}
int endTeam(FILE * f){
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
}

int readTag(char * line , const char * tag, char * buff ){
	char * endtag = (char*) calloc(strlen(tag)+3,sizeof(char));
	char * starttag = (char*) calloc(strlen(tag)+2,sizeof(char));
	sprintf(endtag,"</%s>",tag);
	sprintf(starttag,"<%s>",tag);

	if(!strnncmp(line,starttag) && strstr(line,endtag)){
		size_t start = strlen(starttag);
		size_t end = strlen(endtag);
		size_t len = strlen(line);
		strncpy(buff,&line[start],len-(start+end+1));
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
