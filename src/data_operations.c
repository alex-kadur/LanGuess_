#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/data_operations.h"
#include "../include/utilities.h"
#include "../include/colors.h"

#include "../include/constants.h"
#include "../include/data_structures.h"
#include "../include/globals.h"

//------------------FUNKTIONSIMPLEMENTIERUNGEN------------------//

// Aktualisieren des Dateinamens basierend auf der aktuellenWortlänge
void aktualisieren_datei_name()
{
    // Set the datei name based on the wort laenge
    sprintf(datei_name, "data/optionen_%d.txt", wort_laenge);
}

//==================================================================================================

// Aktualisieren der Optionenliste nach Änderung der Wortlänge
void aktualisieren_optionen_liste()
{   
    // Gibt den für die Knoten in der Liste allokierten Speicher frei
    free_optionen_liste();

    // Oeffnen der Datei
    oeffnen_datei();

    // Aktualisieren der Optionenliste
    einlesen_optionen_datei();
}

//==================================================================================================

// Oeffnen der Datei
void oeffnen_datei()
{
    // Initialisieren des Dateizeigers
    FILE *datei;

    // Öffnen der Datei zum Lesen
    datei = fopen(datei_name, "r");

    // Überprüfen, ob die Datei erfolgreich geöffnet wurde
    if (datei == NULL)
    {
        // Fehlermeldung ausgeben
        printf("Fehler beim Öffnen der Datei.\n");

        // Programm beenden
        exit(1);
    }

    // Schließen der Datei
    fclose(datei);
}

//==================================================================================================

// Einlesen der Optionen aus der Datei
void einlesen_optionen_datei()
{
    // Initialisieren des Dateizeigers
    FILE *datei;

    // Öffnen der Datei zum Lesen
    datei = fopen(datei_name, "r");

    // Überprüfen, ob die Datei erfolgreich geöffnet wurde
    if (datei == NULL)
    {
        // Fehlermeldung ausgeben
        printf(ROT "Fehler beim Öffnen der Datei." RESET "\n");

        // Programm beenden
        exit(1);
    }

    // Initialisiert Puffer zum Speichern des aus der Datei gelesenen Worts
    char puffer[MAX_OPTION_LAENGE];

    // Lesen der Wörter aus der Datei und Hinzufügen an die verkettete Liste
    while (fscanf(datei, "%s", puffer) != EOF)
    {
        // Erstellt neuen Knoten
        struct knoten *neuer_knoten = (struct knoten *)malloc(sizeof(struct knoten));

        // Kopiert Wort in 'option' im neuen Knoten
        strcpy(neuer_knoten->option.wort, puffer);

        // Setzt Länge Worts
        neuer_knoten->option.laenge = strlen(puffer);

        // Setzt den Zeiger auf NULL
        neuer_knoten->naechste = NULL;

        // Fügt neuen Knoten zur verkettete Liste hinzu
        if (optionen == NULL)
        {
            // Wenn die Liste leer ist, wird der neue Knoten das erste Element
            optionen = neuer_knoten;
        }
        else
        {
            // Andernfalls wird der neue Knoten an das Ende der Liste angehängt 
            struct knoten *aktuell = optionen;
            // Schleife bis zum letzten Knoten
            while (aktuell->naechste != NULL)
            {   
                // Gehe zum nächsten Knoten
                aktuell = aktuell->naechste;
            }
            // Hänge den neuen Knoten an das Ende der Liste an
            aktuell->naechste = neuer_knoten;
        }
    }

    // Schließen der Datei
    fclose(datei);
}

//==================================================================================================

// Fuegt eine Option zur Liste hinzu
void hinzufuegen_option_liste()
{
    // Initialisiert Puffers zum Speichern des neuen Worts
    char puffer[MAX_OPTION_LAENGE];

    // Fragt neues Wort vom Benutzer ab
    printf("Neues Wort eingeben: ");
    scanf("%s", puffer);

    // Überprüft, ob die Länge des Worts korrekt ist
    if (strlen(puffer) != wort_laenge)
    {   
        // ggf. Fehlermeldung ausgeben
        printf("\n\n" ROT "Fehler: Wortlaenge muss %d sein." RESET "\n", wort_laenge);

        // Warte auf Benutzereingabe
        warte_auf_eingabe();

        // Zurück zum Menü Optionsverwaltung
        return;
    }

    // Neuen Knoten erstellen
    struct knoten *neuer_knoten = (struct knoten *)malloc(sizeof(struct knoten));

    // Kopiert Wort in 'option' im neuen Knoten
    strcpy(neuer_knoten->option.wort, puffer);

    // Setzt 'laenge' des Worts im neuen Knoten
    neuer_knoten->option.laenge = strlen(puffer);

    // Setzt Zeiger 'naechste' im neuen Knoten auf NULL
    neuer_knoten->naechste = NULL;

    // Fügt neuen Knoten zur verketteten Liste hinzu

    // Wenn die Liste leer ist, wird der neue Knoten das erste Element
    if (optionen == NULL)
    {   
        // Setze den neuen Knoten als erstes Element
        optionen = neuer_knoten;
    }
    else
    {
        // Andernfalls wird der neue Knoten an das Ende der Liste angehängt

        // Initialisiere 'aktuell' als erstes Element
        struct knoten *aktuell = optionen;
        // Schleife bis zum letzten Knoten
        // Wenn 'aktuell->naechste' NULL ist, dann ist 'aktuell' der letzte Knoten
        while (aktuell->naechste != NULL)
        {
            // Gehe zum nächsten Knoten
            aktuell = aktuell->naechste;
        }
        // Hänge den neuen Knoten an das Ende der Liste an
        aktuell->naechste = neuer_knoten;
    }

    // Bestätigungsmeldung für das hinzugefügte Wort
    printf("\n\n" GRUEN "Wort hinzugefuegt: %s" RESET "\n", puffer);

    // Warte auf Benutzereingabe
    warte_auf_eingabe();
}

//==================================================================================================

// Funktion zum Löschen einer Option aus der Liste
void loeschen_option_liste()
{
    // Überprüft, ob die Liste leer ist

    // Falls die Liste leer ist, wird eine Fehlermeldung ausgegeben
    if (liste_leer())
    {
        return;
    }   

    // Gibt die Liste der Wörter nummeriert aus
    ausgeben_optionen_liste();

    // Initialisiert 'nummer', die die Nummer des zu löschenden Worts speichert
    int nummer;

    // Fragt vom Benutzer Nummer des zu löschenden Worts ab
    printf("\nNummer des zu löschenden Worts eingeben: ");
    scanf("%d", &nummer);

    // Überprüft, ob die Nummer gültig ist
    if (nummer < 1)
    {
        // Fehlermeldung ausgeben
        printf("\n\n" ROT "Ungültige Auswahl." RESET "\n");

        // Warte auf Benutzereingabe
        warte_auf_eingabe();

        // Zurück zum Menü Optionsverwaltung
        return;
    }

    // Entfernt das Wort aus der Liste

    // Initialisiert 'aktuell' als erstes Element
    struct knoten *aktuell = optionen;
    // Initialisiert 'vorherige' als NULL
    struct knoten *vorherige = NULL;
    // Initialisiert Zähler
    int zaehler = 1;
    // Schleife bis zum gesuchten Knoten oder bis zum Ende der Liste
    while (aktuell != NULL && zaehler < nummer)
    {
        // Gehe zum nächsten Knoten
        vorherige = aktuell;
        aktuell = aktuell->naechste;
        // Erhöhe den Zähler
        zaehler++;
    }

    // Überprüft, ob das Wort gefunden wurde

    // Falls 'aktuell' NULL ist, wurde das Wort nicht gefunden
    if (aktuell == NULL)
    {
        // Fehlermeldung ausgeben
        printf("\n\n" ROT "Wort nicht gefunden." RESET "\n");

        // Warte auf Benutzereingabe
        warte_auf_eingabe();

        // Zurück zum Menü Optionsverwaltung
        return;
    }

    // Entfernt das Wort aus der Liste
    
    // Wenn 'vorherige' NULL ist, dann ist 'aktuell' das erste Element
    if (vorherige == NULL)
    {
        // Setze das naechste Element als erstes Element
        optionen = aktuell->naechste;
    }
    else
    {
        // Andernfalls wird das naechste Element des vorherigen Elements ...
        // ... auf das naechste Element des aktuellen Elements gesetzt
        vorherige->naechste = aktuell->naechste;
    }

    // Gibt den für den entfernten Knoten allokierten Speicher frei
    free(aktuell);

    // Bestätigungsmeldung für das entfernte Wort
    printf("\n\n" GRUEN "Wort entfernt." RESET "\n");

    // Warte auf Benutzereingabe
    warte_auf_eingabe();
}

//==================================================================================================

// FWählt eine zufällige Option aus der Liste
void select_option_zufall()
{
    // Überprüft, ob die Liste leer ist
    if (liste_leer())
    {
        return;
    }

    // Wählt eine zufällige Option aus der Liste

    // Initialisiert 'aktuell' als erstes Element
    struct knoten *aktuell = optionen;
    // Initialisiere 'zaehler' auf 1
    int zaehler = 1;
    // Schleife bis zum letzten Knoten
    while (aktuell->naechste != NULL)
    {
        // Gehe zum nächsten Knoten
        aktuell = aktuell->naechste;
        // Erhöhe den Zähler
        zaehler++;
    }

    // Generiert eine zufällige Nummer zwischen 1 und der Anzahl der Knoten in der Liste
    // Initialisiert den Zufallszahlengenerator
    srand(time(NULL));
    // rand() gibt eine zufällige Zahl zurück
    int random = rand() % zaehler + 1;

    // Setzt 'aktuell' auf das erste Element
    aktuell = optionen;
    // Setzt 'zaehler' auf 1
    zaehler = 1;
    // Schleife bis zum zufälligen Knoten
    while (aktuell != NULL && zaehler < random)
    {
        // Gehe zum nächsten Knoten
        aktuell = aktuell->naechste;
        // Erhöhe den Zähler
        zaehler++;
    }

    // Kopiert das zufällige Wort in 'option_zufall'
    strcpy(option_zufall, aktuell->option.wort);
}

//==================================================================================================

// Gibt die Optionen aus der Liste aus
void ausgeben_optionen_liste()
{
    // Überprüft, ob die Liste leer ist

    // Falls die Liste leer ist, wird eine Fehlermeldung ausgegeben
    if (liste_leer())
    {
        return;
    }

    // Gibt die Liste der Wörter nummeriert aus

    // Initialisiert 'aktuell' als erstes Element
    struct knoten *aktuell = optionen;
    // Initialisiert Zähler
    int zaehler = 1;
    // Schleife bis zum Ende der Liste
    while (aktuell != NULL)
    {
        // Gibt das Wort mit der Nummer aus
        printf("%2d. %s\n", zaehler, aktuell->option.wort);
        aktuell = aktuell->naechste;
        zaehler++;
    }
}

//==================================================================================================

// Speicher die aktuellen 'optionen' in die entsprechende Datei
void speichern_optionen_datei()
{
    // Initialisiert Dateizeiger
    FILE *datei;

    // Öffnet die Datei zum Schreiben
    datei = fopen(datei_name, "w");

    // Überprüft, ob die Datei erfolgreich geöffnet wurde

    // Falls die Datei nicht geöffnet werden konnte, wird eine Fehlermeldung ausgegeben
    if (datei == NULL)
    {
        // Fehlermeldung ausgeben
        printf(ROT "Fehler beim Öffnen der Datei." RESET "\n");

        // exit(1) beendet das Programm mit einem Fehlercode
        exit(1);
    }

    // Schreibt die Wörter in die Datei

    // Initialisiert 'aktuell' als erstes Element
    struct knoten *aktuell = optionen;
    // Solange 'aktuell' nicht NULL ist
    while (aktuell != NULL)
    {
        // Schreibt das Wort in die Datei
        fprintf(datei, "%s\n", aktuell->option.wort);
        // Gehe zum nächsten Element
        aktuell = aktuell->naechste;
    }

    // Schließt die Datei
    fclose(datei);

    // Bestätigungsmeldung für die gespeicherte Liste der Wörter
    printf(GRUEN "Optionen gespeichert." RESET "\n");

    // Warte auf Benutzereingabe
    warte_auf_eingabe();
}

//==================================================================================================

// Gibt den für die Knoten in der Liste allokierten Speicher frei
void free_optionen_liste()
{
    // Überprüft, ob die Liste leer ist

    // 'aktuell' wird auf das erste Element gesetzt
    struct knoten *aktuell = optionen;

    // Solange 'aktuell' nicht NULL ist
    while (aktuell != NULL)
    {
        // 'temp' wird auf 'aktuell' gesetzt
        struct knoten *temp = aktuell;
        // 'aktuell' wird auf das nächste Element gesetzt
        aktuell = aktuell->naechste;
        // Der Speicher für 'temp' wird freigegeben
        free(temp);
    }

    // Setzt die Optionenliste auf NULL
    optionen = NULL;
}

//==================================================================================================
int liste_leer()
{
    // Überprüft, ob die Liste leer ist

    // Falls die Liste leer ist, wird eine Fehlermeldung ausgegeben
    if (optionen == NULL)
    {
        // Fehlermeldung ausgeben
        printf(ROT "Die Liste ist leer." RESET "\n");

        // Warte auf Benutzereingabe
        warte_auf_eingabe();

        return 1;
    }

    return 0;
}