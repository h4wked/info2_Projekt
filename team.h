#ifndef TEAM_H
#define TEAM_H

#include "datastructure.h"

int createTeam();

int deleteTeam();

int createPlayer(TTeam * newTeam);

void deletePlayer();

void searchPlayer();

void sortTeams();

int listTeams();

void listOneTeam(TTeam * team);

void listOnePlayer(TPlayer * player);

void teamCleanup();

void oneTeamCleanup(TTeam * team);

#endif
