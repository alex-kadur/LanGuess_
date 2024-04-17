#include "functions.h"

int main(void)
{
    // Erlaubt direkten Neustart nach Rundenende
    do
    {
        // Gibt Titel in ASCII-Darstellung aus
        ausgabe_titel();

        // Abfrage Wortlaenge
        // Speichert Eingabe in 'wortlaenge'
        int wortlaenge;
        eingabe_wortlaenge(&wortlaenge);

        leere_screen();

        // Oeffnet Datei entsprechend Wortlaenge
        // Speichert (pseudo)zufaellig 1 Wort aus Liste in 'auswahl'
        char auswahl[wortlaenge + 1];
        if (eingabe_auswahl(wortlaenge, auswahl))
        {
            printf("Fehler beim Oeffnen der Datei %d.txt\n", wortlaenge);
            return 1;
        }

        //======================================================//

        // Erlaubt 'wortlaenge + 1 Versuche
        int versuche = wortlaenge + 1;

        // Bestimmt am Spielende Ergebnis
        // Wert initial ist 0 (verloren)
        int gewonnen = 0;

        // Einleitungstext
        // Farbdarstellung entsprechend Makros
        printf(GRUEN "Willkommen!" RESET "\n\n");
        printf("Sie haben %i Versuche, um das gesuchte Wort mit %i Buchstaben zu erraten ...\n", versuche, wortlaenge);
        ausgabe_linie(77);

        //======================================================//

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

        //======================================================//

        ausgabe_linie(77);

        // Ausgabe des Ergebnisses je nach Wert 'gewonnen'
        // 1 gewonnen
        // 0 verloren
        ausgabe_ergebnis(gewonnen, auswahl);

        // Abfrage ob weitere Runde gewuenscht
    } while (neue_runde("Noch eine Runde?"));

    leere_screen();
}