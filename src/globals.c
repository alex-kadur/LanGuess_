#include <stdio.h>

#include "../include/globals.h"

#include "../include/data_structures.h"
#include "../include/constants.h"

//------------------GLOBALE VARIABLEN------------------//
//-----------------------------------------------------//

// Speichert das zufällig ausgewählte Wort der aktuellen Runde
char option_zufall[MAX_WORT_LAENGE];

// Speichert die aktuelle Länge des Wortes
// Initial wird die Länge des Wortes auf 5 gesetzt
int wort_laenge = 5;

// Speichert den Dateinamen
// Initial wird der Dateiname auf 'optionen_5.txt' gesetzt
char datei_name[MAX_DATEI_NAME_LAENGE] = "data/optionen_5.txt";

// Speichert die Liste der Optionen
// Initial wird die Liste auf NULL gesetzt
// Die Liste wird später mit den Wörtern aus der Datei initialisiert
struct knoten *optionen = NULL;

//-----------------------------------------------------//