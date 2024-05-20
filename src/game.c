#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"

#include "../include/constants.h"
#include "../include/utilities.h"
#include "../include/colors.h"

//------------------BESCHREIBUNG------------------//

// Funktionen zur Durchfuehrung des eigentlichen Spiels

// Gibt Legende aus
// Startet eine Schleife mit max. Wortlaenge + 1 Durchlaufen
    // Pro Durchlauf:
    // Fordert Nutzer zur Eingabe eines Wortes auf
    // Vergibt zunaechst fuer jede Position im Wort den Status FALSCH
    // Vergleicht Nutzereingabe mit Zufallswort dieser Runde
    // Fuer jede Position im Wort:
    // Aktualisiert Status entsprechend KORREKT oder FAST (siehe Kommentare zur funktion)
    // Aktualisiert Gesamtwertung entsprechend

//------------------FUNKTIONSIMPLEMENTIERUNGEN------------------//

int starte_spiel(int wortlaenge, char auswahl[])
{

        // Erlaubt 'wortlaenge + 1 Versuche
        int versuche = wortlaenge + 1;

        // Bestimmt am Spielende Ergebnis
        // Wert initial ist 0 (verloren)
        int gewonnen = 0;

        // Einleitungstext
        // Farbdarstellung entsprechend Makros
        printf(GRUEN "Los geht's!" RESET "\n\n");
        printf("Sie haben %i Versuche, um das gesuchte Wort mit %i Buchstaben zu erraten ...\n\n", versuche, wortlaenge);
        printf(GRUEN "o" RESET " = Buchstabe steht an korrekter Position im Wort\n");
        printf(GELB "o" RESET " = Buchstabe kommt an anderer Position im Wort vor\n");
        printf(ROT "o" RESET " = Buchstabe kommt nicht im Wort vor\n");
        ausgabe_linie(77);

        // Schleife mit einem Durchlauf pro Versuch
        for (int i = 0; i < versuche; i++)
        {
            // Abfrage des aktuellen Versuchs
            char versuch[wortlaenge + 1];
            eingabe_versuch(versuch, wortlaenge);

            // Array, dass spaeter die Auswertung der einzelnen Buchstaben enthaelt
            int status[wortlaenge];

            // Setzt alle Elemente des Arrys 'status' initial auf FALSCH (0)
            for (int j = 0; j < wortlaenge; j++)
            {
                status[j] = FALSCH;
            }

            // Vergleicht 'versuch' mit 'auswahl'
            // Vergibt entsprechend Punkte entsprechend Makros
            // Speichert Summe Punkte in 'wertung'
            int wertung = pruefe_wort(versuch, wortlaenge, status, auswahl);

            // Ausgabe Wort 'versuch' Buchstabe fuer Buchstabe
            // Farbdarstellung entsprechend uebereinstimmung 'status' mit Makro-Werten
            printf("%d. versuch: ", i + 1);
            ausgabe_wort(versuch, wortlaenge, status);

            // Falls Summe Wertung Versuch == TREFFER * 'wortlaenge' ...
            // ... ueberschreibt 'gewonnen' mit 1
            pruefe_gewonnen(&gewonnen, wertung, wortlaenge);

            if (gewonnen)
            {
                break;
            }
        }

        ausgabe_linie(77);

        // Ausgabe des Ergebnisses je nach Wert 'gewonnen'
        // 1 gewonnen
        // 0 verloren
        ausgabe_ergebnis(gewonnen, auswahl);
}

//==================================================================================================

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

//==================================================================================================

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

//==================================================================================================

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

//==================================================================================================

// Falls Summe Wertung Versuch == TREFFER * 'wortlaenge' ...
// ... ueberschreibt 'gewonnen' mit 1
void pruefe_gewonnen(int *gewonnen, int wertung, int wortlaenge)
{
    if (wertung == TREFFER * wortlaenge)
    {
        *gewonnen = 1;
    }
}

//==================================================================================================

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

//==================================================================================================