#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "utility_functions.h"

// Jede Textdatei beinhalted exakt LISTELAENGE Woerter
#define LISTELAENGE 50

// Werte fuer Farben und wertung
// TREFFER == korrekter Buchstabe an korrekter Position; priorisierte Darstellung
// FAST == Buchstabe kommt an abweichender Position vor; beruecksichtigt Anzahl Vorkommen; nachrangige Darstellung
// FALSCH == Buchstabe kommt nicht im Wort vor; Default-Wert
#define TREFFER 2
#define FAST 1
#define FALSCH 0

// ANSI Farbcodes Zeichen und Hintergrund
#define GRUEN "\e[38;2;255;255;255;1m\e[48;2;0;127;0;1m"
#define GELB "\e[38;2;255;255;255;1m\e[48;2;127;127;0;1m"
#define ROT "\e[38;2;255;255;255;1m\e[48;2;127;0;0;1m"
#define RESET "\e[0;39m"

//======================================================//

// Funktionsprototypen
void ausgabe_titel();
void eingabe_wortlaenge(int *wortlaenge);
int eingabe_auswahl(int wortlaenge, char auswahl[]);
void eingabe_versuch(char versuch[], int wortlaenge);
void zaehle_buchstabe(char wort[], int wortlaenge, int zaehler[]);
int verarbeite_korrekt(char versuch[], char auswahl[], int status[], int auswahl_zaehler[], int wortlaenge);
int verarbeite_fast(char versuch[], char auswahl[], int status[], int auswahl_zaehler[], int wortlaenge);
int pruefe_wort(char versuch[], int wortlaenge, int status[], char auswahl[]);
void ausgabe_wort(char versuch[], int wortlaenge, int status[]);
void ausgabe_ergebnis(int gewonnen, char auswahl[]);

//======================================================//

// Gibt den Titel als ASCII-Design aus
// Nutzt Macros zum Farbwechsel/-reset
void ausgabe_titel(void)
{
    leere_screen();

    printf("\n\n");
    printf(GELB "██╗     ███████╗" GRUEN "██╗  ██╗" GELB "██╗ ██████╗ ██╗   ██╗███████╗███████╗███████╗" ROT "        " RESET "\n");
    printf(GELB "██║     ██╔════╝" GRUEN "╚██╗██╔╝" GELB "██║██╔════╝ ██║   ██║██╔════╝██╔════╝██╔════╝" ROT "        " RESET "\n");
    printf(GELB "██║     █████╗  " GRUEN " ╚███╔╝ " GELB "██║██║  ███╗██║   ██║█████╗  ███████╗███████╗" ROT "        " RESET "\n");
    printf(GELB "██║     ██╔══╝  " GRUEN " ██╔██╗ " GELB "██║██║   ██║██║   ██║██╔══╝  ╚════██║╚════██║" ROT "        " RESET "\n");
    printf(GELB "███████╗███████╗" GRUEN "██╔╝ ██╗" GELB "██║╚██████╔╝╚██████╔╝███████╗███████║███████║" ROT "███████╗" RESET "\n");
    printf(GELB "╚══════╝╚══════╝" GRUEN "╚═╝  ╚═╝" GELB "╚═╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝╚══════╝" ROT "╚══════╝" RESET "\n");
    printf("\n\n");
}

//======================================================//

// Fragt von Nutzer die Wortlaenge ab und ...
// ... stellt sicher, dass Eingabe 5, 6, 7, oder 8 ist
// Speichert Wert ueber Pointer in 'wortlaenge'
void eingabe_wortlaenge(int *wortlaenge)
{
    do
    {
        printf("Wortlaenge (5, 6, 7, oder 8): ");
        scanf("%d", wortlaenge);
        leere_eingabepuffer();

        if (*wortlaenge < 5 || *wortlaenge > 8)
        {
            printf("Wortlaenge muss 5, 6, 7, oder 8 sein!\n\n");
        }

    } while (*wortlaenge < 5 || *wortlaenge > 8);
}

//======================================================//

// Oeffnet Datei entsprechend Wortlaenge
// Speichert Woerter aus Datei in Array 'optionen'
// Waehlt (pseudo)zufaellig 1 Wort aus
// Speichert auswahl in 'auswahl'
int eingabe_auswahl(int wortlaenge, char auswahl[])
{
    // Datei entsprechend Wortlaenge oeffnen
    char dateiname[50];
    sprintf(dateiname, "files/%i.txt", wortlaenge);
    FILE *wortliste = fopen(dateiname, "r");
    if (wortliste == NULL)
    {
        return 1;
    }

    // Woerter aus Datei in Array mit LISTELAENGE speichern
    char optionen[LISTELAENGE][wortlaenge + 1];
    for (int i = 0; i < LISTELAENGE; i++)
    {
        fscanf(wortliste, "%s", optionen[i]);
    }

    // (pseudo)zufaellig 1 Wort auswaehlen
    srand(time(NULL));
    strcpy(auswahl, optionen[rand() % LISTELAENGE]);

    return 0;
}

//======================================================//

// Speichert Nutzereingabe in Array 'versuch'
void eingabe_versuch(char versuch[], int wortlaenge)
{

    char temp[wortlaenge];
    // Stell sicher, dass Laenge der Nutzereingabe korrekt
    do
    {
        printf("\nWort mit %i Buchstaben: ", wortlaenge);
        scanf("%s", temp);
        leere_eingabepuffer();

    } while (wortlaenge != strlen(temp));

    // Pruefung auf Grossschreibung und ggf. Umwandlung zu klein
    umwandlung_kleinbuchstaben(temp);

    strcpy(versuch, temp);
}

//======================================================//

// Hilfsfunktion fuer pruefe_wort()
// Zaehlt das vorkommen der Buchstaben in einem Wort
// Zahlt elemente im Arry 'zaehler[]' hoch
void zaehle_buchstabe(char wort[], int wortlaenge, int zaehler[])
{
    for (int i = 0; i < wortlaenge; i++)
    {
        // Bestimmt position Buchstabe im Alphabet/Arry ueber ASCII-Werte
        // Bsp. wort[i] == 'b'; 'b' - 'a' = 1; 'b' steht an position 1
        zaehler[wort[i] - 'a']++;
    }
}

// Hilfsfunktion fuer pruefe_wort()
// Vergleicht Buchstabe fuer Buchstabe 'auswahl' und 'versuch' ...
// ... und sucht nach TREFFER.
// Passt 'status' der Positionen mit TREFFER an
// Reduziert Buchstabenzahler um Anzahl TREFFER
// Gibt Gesamtwertung fuer alle TREFFER zurueck
int verarbeite_korrekt(char versuch[], char auswahl[], int status[], int auswahl_zaehler[], int wortlaenge)
{
    int wertung = 0;
    for (int i = 0; i < wortlaenge; i++)
    {
        // Bedingung: Buchstabe[i] im 'versuch' == Buchstabe[i] in 'auswahl' ...
        // ... und verbleibende Anzahl Buchstabe (gleich mit Buchstabe[i] im 'versuch') in 'auswahl_zaehler' > 0
        if (versuch[i] == auswahl[i] && auswahl_zaehler[versuch[i] - 'a'] > 0)
        {
            // Position[i] als TREFFER (2) definiert
            status[i] = TREFFER;
            // 'wertung' um TREFFER (2) erhoeht
            wertung += TREFFER;
            // verbleibende Anzahl Buchstabe (gleich mit Buchstabe[i] im 'versuch') in 'auswahl_zaehler' um 1 verringert
            auswahl_zaehler[versuch[i] - 'a']--;
        }
    }
    // Gibt Summe der 'wertung' fuer alle TREFFER zurueck
    return wertung;
}

// Hilfsfunktion fuer pruefe_wort()
// Prueft Buchstabe fuer Buchstabe alle 'position' die kein TREFFER ...
// ... und sucht nach FAST d.h. Buchstabenwert der Position kommt im Wort vor ('auswahl_zahler' > 0)
// Passt 'status' der Positionen mit FAST an
// Reduziert Buchstabenzahler um Anzahl FAST
// Gibt Gesamtwertung fuer alle FAST zurueck
int verarbeite_fast(char versuch[], char auswahl[], int status[], int auswahl_zaehler[], int wortlaenge)
{
    int wertung = 0;
    for (int i = 0; i < wortlaenge; i++)
    {
        // Bedingung: status Buchstabe[i] nicht TREFFER ...
        // ... und verbleibende Anzahl Buchstabe (gleich mit Buchstabe[i] im 'versuch') in 'auswahl_zaehler' > 0
        if (status[i] != TREFFER && auswahl_zaehler[versuch[i] - 'a'] > 0)
        {
            // Position[i] als FAST (1) definiert
            status[i] = FAST;
            // 'wertung' um FAST (1) erhoeht
            wertung += FAST;
            // verbleibende Anzahl Buchstabe (gleich mit Buchstabe[i] im 'versuch') in 'auswahl_zaehler' um 1 verringert
            auswahl_zaehler[versuch[i] - 'a']--;
        }
    }
    // Gibt Summe der 'wertung' fuer alle FAST zurueck
    return wertung;
}

// Hauptfunktion zum Vergleich von 'versuch' und 'auswahl'
// Vergibt entsprechende Werte fuer KORREKT und FAST in 'status'
// Gibt Gesamtwertung entsprechend Vorkommen von KORREKT und FAST zurueck
int pruefe_wort(char versuch[], int wortlaenge, int status[], char auswahl[])
{
    int wertung = 0;

    // Initialisiert Zaehler-Array mit allen Elementen Wert 0;
    // 26 um alle Buchstaben Alphabet zu enthalten
    int auswahl_zaehler[26] = {0};

    // Zahlt Vorkommen einzelner Elemente/Buchstaben in Arrays 'auswahl' und 'versuch'
    // Ueber 'auswahl_zaehler' und 'versuch_zaehler' hochgezaehlt
    zaehle_buchstabe(auswahl, wortlaenge, auswahl_zaehler);

    // Vergleicht 'versuch' und 'auswahl' im Hinlick auf KORREKT und FAST...
    // Verarbeitung von FALSCH unnoetig, da 'status' ohnehin mit 0 initialisiert
    // Vergibt entsprechende Werte in 'status'
    // Erhoeht Gesamtwertung 'wertung' um Teilwertungen aus Rueckgabe
    wertung += verarbeite_korrekt(versuch, auswahl, status, auswahl_zaehler, wortlaenge);
    wertung += verarbeite_fast(versuch, auswahl, status, auswahl_zaehler, wortlaenge);

    // Gibt Gesamtwertung zurueck
    return wertung;
}

//======================================================//

// Ausgabe Wort 'versuch' Buchstabe fuer Buchstabe
// Farbdarstellung entsprechend uebereinstimmung 'status' mit Makro-Werten
void ausgabe_wort(char versuch[], int wortlaenge, int status[])
{
    for (int i = 0; i < wortlaenge; i++)
    {
        if (status[i] == TREFFER)
        {
            printf(GRUEN "%c" RESET, versuch[i]);
        }
        else if (status[i] == FAST)
        {
            printf(GELB "%c" RESET, versuch[i]);
        }
        else
        {
            printf(ROT "%c" RESET, versuch[i]);
        }
    }
    printf("\n");
}

//======================================================//

// Falls Summe Wertung Versuch == TREFFER * 'wortlaenge' ...
// ... ueberschreibt 'gewonnen' mit 1
void pruefe_gewonnen(int *gewonnen, int wertung, int wortlaenge)
{
    if (wertung == TREFFER * wortlaenge)
    {
        *gewonnen = 1;
    }
}

//======================================================//

// Gibt das Ergebnis der Runde aus
void ausgabe_ergebnis(int gewonnen, char auswahl[])
{
    if (gewonnen)
    {
        printf("\n" GRUEN "Gewonnen!" RESET "\n\n\n");
    }
    else
    {
        printf("\n" ROT "Verloren!" RESET "\n");
        printf("\nDas gesuchte Wort war: " GRUEN "%s" RESET "\n\n", auswahl);
    }
}

//======================================================//