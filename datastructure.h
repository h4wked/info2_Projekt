#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define MAXPLAYER 23

#define MAXNAMELENGTH 40

#define MAXINDEX 307


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

struct TTeam
{
    char * name;
    char * coach;
    int numberOfPlayers;
    TPlayer player[MAXPLAYER];
    TTeam * nextTeam;
    TTeam * prevTeam;

};

typedef struct TListElement TListElement;

typedef struct TListElement
{
    TTeam * Team;
    TPlayer * Player;
    TListElement * next;
};

typedef struct THashTableElement THashTableElement;

typedef struct THashTableElement
{
    TListElement * first;
    TListElement * last;
};

extern TTeam * firstTeam;
extern TTeam * lastTeam;
extern THashTableElement PlayerIndex[MAXINDEX];
#endif
