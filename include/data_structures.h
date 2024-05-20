#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "constants.h"

//------------------DATENSTRUKTUREN------------------//
//---------------------------------------------------//

struct option
{
    char wort[MAX_WORT_LAENGE];
    int laenge;
};

struct knoten
{
    struct option option;
    struct knoten *naechste;
};

//---------------------------------------------------//

#endif