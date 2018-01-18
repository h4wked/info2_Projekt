#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

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
        if(compareTeamNames(currentTeam, newTeam) > 0)  //suche namensposition innerhalb der liste
            {
            firstTeam->prevTeam = newTeam;
            newTeam->nextTeam = firstTeam;
            firstTeam = newTeam;
            return EXIT_SUCCESS;
            }
            else
            {
                while(currentTeam != lastTeam)
                {
                    currentTeam = currentTeam->nextTeam;
                    if(compareTeamNames(currentTeam, newTeam) > 0)
                    {
                        TTeam * prevTeam = currentTeam->prevTeam;
                        currentTeam->prevTeam = newTeam;
                        prevTeam->nextTeam = newTeam;
                        newTeam->nextTeam = currentTeam;
                        newTeam->prevTeam = prevTeam;
                        return EXIT_SUCCESS;
                    }
                }
                lastTeam->nextTeam = newTeam;
                newTeam->prevTeam = lastTeam;
                lastTeam = newTeam;
                return EXIT_SUCCESS;
            }
            /*
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

        }
        else    //füge neues team in liste ein
        {
            TTeam * prevTeam = currentTeam->prevTeam;
            prevTeam->nextTeam = newTeam;                   //lasse team vor und hinter newTeam auf dieses zeigen
            currentTeam->prevTeam = newTeam;
            newTeam->prevTeam = prevTeam;                   //lasse neues Team auf teams vor und hinter ihm zeigen
            newTeam->nextTeam = currentTeam;
        }*/
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
        nextTeam->prevTeam = NULL;
    }
    else if(team == lastTeam)                       //entfernen von lastTeam
    {
        lastTeam = team->prevTeam;
        prevTeam->nextTeam = NULL;
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

int appendInEVList(THashTableElement * tableElement, TTeam * team, TPlayer * player)
{
    //List Element erstellen
    TListElement * listElement = malloc(sizeof(TListElement));
    listElement->Player = player;
    listElement->Team = team;
    //List ELement einhängen
    if(tableElement->first == NULL)
    {       //wenn erstes
        listElement->next = NULL;
        tableElement->first = listElement;
        tableElement->last = listElement;
        return EXIT_SUCCESS;
    }
    else
    {       //wenn zusätzliches
        tableElement->last->next = listElement;
        tableElement->last = listElement;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int removeFromEVList(THashTableElement * tableElement, TPlayer * player)
{
    if(tableElement->first == NULL)
    {
        perror("error in removeFromEVList");
        return EXIT_FAILURE;
    }
    if(tableElement->first == tableElement->last)
    {       //Behandlung wenn nur ein tableELement in PlayerIndex
        if(player == tableElement->first->Player)
        {
            free(tableElement->first);
            tableElement->first = NULL;
            tableElement->last = NULL;
            return EXIT_SUCCESS;
        }
        perror("error in removeFromEVList");
        return EXIT_FAILURE;
    }
    else
    {   //Behandlung wenn mehrere Elemente in PlayerIndex
        TListElement * currentElement = tableElement->first;
        while(currentElement->Player != player)
        {   //springen zum zu löschenden Element
            if(currentElement->next == NULL)
            {   //Player in liste nicht gefunden
                perror("error in removeFromEVList");
                return EXIT_FAILURE;
            }
            currentElement = currentElement->next;
        }

        if(currentElement == tableElement->first)
        {   //zu löschendes ELement erstes in der liste
            tableElement->first = tableElement->first->next;
            free(currentElement);
            return EXIT_SUCCESS;
        }
        else if(currentElement == tableElement->last)
        {   //zu löschendes Element letztes in der Liste
            TListElement * prevElement = tableElement->first;
            while(prevElement->next != currentElement)
            {   //finde element vor dem letzten
                prevElement = prevElement->next;
            }
            prevElement->next = NULL;
            tableElement->last = prevElement;
            free(currentElement);
            return EXIT_SUCCESS;
        }
        else
        {   //zu löschendes Element in mitten der Liste
            TListElement * prevElement = tableElement->first;
            while(prevElement->next != currentElement)
            {   //finde element vor dem letzten
                prevElement = prevElement->next;
            }
            prevElement->next = currentElement->next;
            free(currentElement);
            return EXIT_SUCCESS;
        }
    }
}


