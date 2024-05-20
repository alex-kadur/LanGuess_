#include <stdio.h>
#include <stdlib.h>

#include "../include/utilities.h"

//------------------FUNKTIONSIMPLEMENTIERUNGEN------------------//

// Gibt eine Linie mit Breite entsprechend Uebergabewert aus
void ausgabe_linie(int laenge)
{
    if (laenge < 0)
    {
        laenge = 0;
    }

    printf("\n");
    for (int i = 0; i < laenge; i++)
    {
        printf("=");
    }
    printf("\n");
}

//==================================================================================================

// Leert den Eingabepuffer
void leere_eingabepuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//==================================================================================================

// Gibt String entsprechend Uebergabewert aus
// Fordert Nutzer zur Eingabe (j/n) auf
// Rueckgabewert 1 falls 'j' oder 'J'
// Sonst Rueckgabewert 0
int auswahl_jn(char *text)
{
    char temp;
    printf("%s (j/n) -> ", text);
    scanf(" %c", &temp);
    if (temp == 'j' || temp == 'J')
    {
        return 1;
    }

    return 0;
}

//==================================================================================================

// Wandelt Zeichen im Uebergabe-Array von Gross- zu Kleinbuchstaben um
void umwandlung_kleinbuchstaben(char input[])
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Prueft ob Zeichen Grossbuchstabe
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            // Umwandlung in Kleinbuchstabe
            input[i] = input[i] + 32;
        }
    }
}

//==================================================================================================

// Leert den Bildschirm unabhaengig vom Betriebssystem
void leere_bild(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//==================================================================================================

// Wartet auf Nutzereingabe
void warte_auf_eingabe(void)
{
    printf("\nWeiter mit Enter ...");

    // Warte auf Nutzereingabe
    getchar();

    // Leere Eingabepuffer
    leere_eingabepuffer();    
}

//==================================================================================================