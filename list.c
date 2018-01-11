int insertInDVList(TTeam * newTeam)
{
    //empty list
    if(firstTeam == NULL)
    {
        firstTeam = newTeam;
        lastTeam = newTeam;
    }else if(firstTeam == lastTeam)     //only one Team
    {
        if(compareTeamNames(newTeam, firstTeam) < 0)
        {
            firstTeam = newTeam;
        /*}else if(compareTeamNames(newTeam, firstTeam) == 0)
        {
            printf("Teamname bereits vorhanden! Breche ab!\n");
            sleep(1);
            oneTeamCleanup(newTeam);
            return EXIT_FAILURE;
        */}else
        {
            lastTeam = newTeam;
        }
        firstTeam->nextTeam = lastTeam;
        lastTeam->prevTeam = firstTeam;
    }
    else                //several Teams
    {
        TTeam * currentTeam = firstTeam;
        while(compareTeamNames(currentTeam, newTeam) > 0)  //suche namensposition innerhalb der liste
                {
                    if(currentTeam == lastTeam) //letztes team erreicht, neues Team noch immer "groesser"
                    {
                        lastTeam->nextTeam = newTeam;
                        newTeam->prevTeam = lastTeam;
                        lastTeam = newTeam;
                        return EXIT_SUCCESS;
                    }
                   currentTeam = currentTeam->nextTeam;
                }
        if(currentTeam == firstTeam) //namenssuche beendet einfügen beginnt, prüfung ob neues team > first team
        {
            firstTeam->prevTeam = newTeam;
            newTeam->nextTeam = firstTeam;
            firstTeam = newTeam;
            return EXIT_SUCCESS;
        }
        else    //füge neues team in liste ein
        {
            TTeam * prevTeam = currentTeam->prevTeam;
            prevTeam->nextTeam = newTeam;                   //lasse team vor und hinter newTeam auf dieses zeigen
            currentTeam->prevTeam = newTeam;
            newTeam->prevTeam = prevTeam;                   //lasse neues Team auf teams vor und hinter ihm zeigen
            newTeam->nextTeam = currentTeam;
        }
    }
}

void removeFromDVList(TTeam * team) 
{
    TTeam * nextTeam = team->nextTeam;
    TTeam * prevTeam = team->prevTeam;

    if(firstTeam == lastTeam)
    {
        firstTeam = NULL;                           //entfernen falls nur ein Team vorhanden
        lastTeam = NULL;
    }
    else if(team == firstTeam)                      //entfernen von firstTeam
    {
        firstTeam = team->nextTeam;
    }
    else if(team == lastTeam)                       //entfernen von lastTeam
    {
        lastTeam = team->prevTeam;
    }
    else
    {
        nextTeam->prevTeam = prevTeam;                      //entferne Team aus der chain
        prevTeam->nextTeam = nextTeam;
    }

    oneTeamCleanup(team);
    free(team);
}


int compareTeamNames(TTeam * a, TTeam * b)
{
    return strcmp(a->name, b->name);
}



