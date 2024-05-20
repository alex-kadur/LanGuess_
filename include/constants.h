#ifndef CONSTANTS_H
#define CONSTANTS_H

//------------------KONSTANTEN------------------//
//----------------------------------------------//

#define MAX_WORT_LAENGE 8
#define MAX_OPTION_LAENGE 8
#define MAX_DATEI_NAME_LAENGE 20
#define MAX_OPTIONEN 100

// TREFFER == korrekter Buchstabe an korrekter Position; priorisierte Darstellung
// FAST == Buchstabe kommt an abweichender Position vor; beruecksichtigt Anzahl Vorkommen; nachrangige Darstellung
// FALSCH == Buchstabe kommt nicht im Wort vor; Default-Wert
#define TREFFER 2
#define FAST 1
#define FALSCH 0

//----------------------------------------------//

#endif