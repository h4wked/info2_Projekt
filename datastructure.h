#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define MAXPLAYER 23

#define MAXNAMELENGTH 40


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

typedef struct TTeam TTeam;

typedef struct TTeam
{
    char * name;
    char * coach;
    int numberOfPlayers;
    TPlayer player[MAXPLAYER];
    TTeam * nextTeam;
    TTeam * prevTeam;

};

extern TTeam *firstTeam;
extern TTeam *lastTeam;
extern int TeamCounter;

#endif
