#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "utilities.h"

// Jede Textdatei beinhalted exakt LISTELAENGE Woerter
#define LISTELAENGE 50

// Werte fuer Farben und wertung
// TREFFER == right letter, right place;
// FAST == right letter, FALSCH place;
// FALSCH == FALSCH letter
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

// Vergleicht 'versuch' mit 'auswahl'
// Vergibt entsprechend Punkte entsprechend Makros
// Speichert Summe Punkte in 'wertung'
int pruefe_wort(char versuch[], int wortlaenge, int status[], char auswahl[])
{
    int wertung = 0;

    // Prueft jeden Buchstaben ...
    for (int i = 0; i < wortlaenge; i++)
    {
        // ... auf Treffer an exakter Position
        if (versuch[i] == auswahl[i])
        {
            status[i] = TREFFER;
            wertung += TREFFER;
            continue;
        }

        // ... auf treffer an abweichender Position
        for (int j = 0; j < wortlaenge; j++)
        {
            if (versuch[i] == auswahl[j])
            {
                status[i] = FAST;
                wertung += FAST;
                continue;
            }
        }
    }

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