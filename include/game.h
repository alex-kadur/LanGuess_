#ifndef GAME_H
#define GAME_H

//------------------FUNKTIONSPROTOTYPEN------------------//
//-------------------------------------------------------//

int starte_spiel(int wortlaenge, char auswahl[]);
void eingabe_wortlaenge(int *wortlaenge);
int eingabe_auswahl(int wortlaenge, char auswahl[]);
void eingabe_versuch(char versuch[], int wortlaenge);
void zaehle_buchstabe(char wort[], int wortlaenge, int zaehler[]);
int verarbeite_korrekt(char versuch[], char auswahl[], int status[], int auswahl_zaehler[], int wortlaenge);
int verarbeite_fast(char versuch[], char auswahl[], int status[], int auswahl_zaehler[], int wortlaenge);
int pruefe_wort(char versuch[], int wortlaenge, int status[], char auswahl[]);
void ausgabe_wort(char versuch[], int wortlaenge, int status[]);
void pruefe_gewonnen(int *gewonnen, int wertung, int wortlaenge);
void ausgabe_ergebnis(int gewonnen, char auswahl[]);

//-------------------------------------------------------//

#endif // GAME_H