#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define MAXPLAYER 23

extern int TeamCounter;


typedef struct {

    int Day;
    int Month;
    int Year;

} TDate;

typedef struct {

    int Second;
    int Minute;
    int Hour;

} TTime;

typedef struct {
    char * name;
    TDate * birthday;
    int nr;
    int goals;
}TPlayer;

typedef struct {
    char * name;
    char * coach;
    int numberOfPlayers;
    TPlayer player[MAXPLAYER];
}TTeam;

extern TTeam Teams[];

#endif
