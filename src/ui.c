#include <stdio.h>
#include <stdlib.h>

#include "../include/ui.h"
#include "../include/utilities.h"
#include "../include/data_operations.h"
#include "../include/game.h"

#include "../include/colors.h"
#include "../include/globals.h"

//------------------FUNKTIONSIMPLEMENTIERUNGEN------------------//

// Ruft den Titelbildschirm auf
void titel_bild()
{
    // Bildschirm leeren
    leere_bild();

    // Titel ausgeben
    ausgabe_titel();
    printf("by Alexander Kadur\n");

    // Warte auf Eingabe
    warte_auf_eingabe();
}

//==================================================================================================

// Gibt den Titel als ASCII-Design aus
// Nutzt Macros zum Farbwechsel/-reset
void ausgabe_titel(void)
{
    leere_bild();

    printf("\n\n");
    printf(GRUEN "                            " RESET "         " ROT "                                           " RESET "\n");
    printf(GRUEN "  ██╗      █████╗ ███╗   ██╗" RESET " ██████╗ " ROT "██╗   ██╗███████╗███████╗███████╗          " RESET "\n");
    printf(GRUEN "  ██║     ██╔══██╗████╗  ██║" RESET "██╔════╝ " ROT "██║   ██║██╔════╝██╔════╝██╔════╝          " RESET "\n");
    printf(GRUEN "  ██║     ███████║██╔██╗ ██║" RESET "██║  ███╗" ROT "██║   ██║█████╗  ███████╗███████╗          " RESET "\n");
    printf(GRUEN "  ██║     ██╔══██║██║╚██╗██║" RESET "██║   ██║" ROT "██║   ██║██╔══╝  ╚════██║╚════██║          " RESET "\n");
    printf(GRUEN "  ███████╗██║  ██║██║ ╚████║" RESET "╚██████╔╝" ROT "╚██████╔╝███████╗███████║███████║███████╗  " RESET "\n");
    printf(GRUEN "  ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝" RESET " ╚═════╝ " ROT " ╚═════╝ ╚══════╝╚══════╝╚══════╝╚══════╝  " RESET "\n");
    printf(GRUEN "                            " RESET "         " ROT "                                           " RESET "\n");

    printf("\n");
}

//==================================================================================================

// Ruft das Hauptmenue auf
void haupt_menu()
{
    // Leert den Bildschirm
    leere_bild();

    // Gibt Hauptmenue aus
    printf(GRUEN "HAUPTMENUE" RESET "\n\n");
    printf("1. Spielen\n");
    printf("2. Wortlaenge Anpassen\n");
    printf("3. Optionen Verwalten\n");
    printf("4. Beenden\n");

    // Initialisiert Variable fuer Nutzereingabe
    int choice;

    // Fragt Nutzer nach Eingabe und speichert in Variable 'choice'
    printf("\nAuswahl: ");
    scanf("%d", &choice);

    // Userauswahl verarbeiten
    switch (choice)
    {
    case 1:
        spiel();
        break;
    case 2:
        wort_laenge_bild();
        break;
    case 3:
        verwalte_optionen_menu();
        break;
    case 4:
        programm_beenden_bild();
        break;
    default:
        // Fehlermeldung bei ungueltiger Eingabe
        printf("\n\n" ROT "Ungueltige Auswahl." RESET "\n");

        // Warte auf Eingabe
        warte_auf_eingabe();

        // Rueckkehr zum Hauptmenue
        haupt_menu();
        break;
    }
}

//==================================================================================================

// Ruft Screen zur Eingabe der Wortlaenge auf
void wort_laenge_bild()
{
    // Leer den Bildschirm
    leere_bild();

    // Fordert Nutzer zur Eingabe einer Zahl zwischen 5 und 8 auf
    printf("Geben Sie eine Zahl zwischen 5 und 8 ein: ");
    // Speichert Eingabe in Variable 'wort_laenge'
    scanf("%d", &wort_laenge);

    // Ueberprueft ob Eingabe zwischen 5 und 8 liegt
    if (wort_laenge < 5 || wort_laenge > 8)
    {
        // Fehlermeldung bei ungueltiger Eingabe
        printf("\n\n" ROT "Ungueltige Eingabe." RESET "\n");

        // Warte auf Eingabe
        warte_auf_eingabe();

        // Rueckkehr zum Hauptmenue
        haupt_menu();
        return;
    }

    // Aktualisiert Dateinamen entsprechend neuer Wortlaenge
    aktualisieren_datei_name();

    // Aktualisiert Optionenliste entsprechend neuer Wortlaenge
    aktualisieren_optionen_liste();

    // Bestaetigung der Aenderung
    printf("\n\n" GRUEN "Wortlaenge geaendert auf: %d." RESET "\n", wort_laenge);

    // Warte auf Eingabe
    warte_auf_eingabe();

    // Rueckkehr zum Hauptmenue
    haupt_menu();
    return;
}

//==================================================================================================

// Startet das Spiel
void spiel()
{
    // Schleife erlaubt direkten Neustart nach Rundenende
    do
    {
        // Leert den Bildschirm
        leere_bild();

        // Zufaelliges Wort aus Optionenliste auswaehlen ...
        // ... und in 'option_zufall' speichern
        select_option_zufall();

        // Startet das Spiel mit zufaelligem Wort
        starte_spiel(wort_laenge, option_zufall);

    // Schleife wird durch Nutzereingabe beendet
    } while (auswahl_jn("Noch eine Runde?"));

    // Rueckkehr zum Hauptmenue
    haupt_menu();
}

//==================================================================================================

// Ruft Menue zur Verwaltung der Optionen auf
void verwalte_optionen_menu()
{
    // Leert den Bildschirm
    leere_bild();

    // Gibt Menue zur Verwaltung der Optionen aus
    printf(GRUEN "OPTIONEN VERWALTEN" RESET "\n\n");
    printf("1. Option Hinzufuegen\n");
    printf("2. Option Entfernen\n");
    printf("3. Optionen Anzeigen\n");
    printf("4. Speichern\n");
    printf("5. Zurueck\n");

    // initialisiert Variable fuer Nutzereingabe
    int choice;

    // Fragt Nutzer nach Eingabe und speichert in Variable 'choice'
    printf("\nAuswahl: ");
    scanf("%d", &choice);

    // Userauswahl verarbeiten
    switch (choice)
    {
    case 1:
        option_hinzufuegen_bild();
        break;
    case 2:
        option_entfernen_bild();
        break;
    case 3:
        optionen_ausgeben_bild();
        break;
    case 4:
        optionen_speichern_bild();
        break;
    case 5:
        haupt_menu();
        break;
    default:
        // Fehlermeldung bei ungueltiger Eingabe
        printf("\n\n" ROT "Ungueltige Auswahl." RESET "\n");

        // Warte auf Eingabe
        warte_auf_eingabe();

        // Rueckkehr zum Verwaltungsmenue
        verwalte_optionen_menu();
        break;
    }
}

//==================================================================================================

// Ruft Screen zum Hinzufuegen einer Option auf
void option_hinzufuegen_bild()
{
    // Leert den Bildschirm
    leere_bild();

    // Ruft Funktion zum Hinzufuegen einer Option auf
    hinzufuegen_option_liste();

    // Rueckkehr zum Verwaltungsmenue
    verwalte_optionen_menu();
}

//==================================================================================================

// Ruft Screen zum Entfernen einer Option auf
void option_entfernen_bild()
{
    // Leert den Bildschirm
    leere_bild();

    // Ruft Funktion zum Entfernen einer Option auf
    loeschen_option_liste();

    // Rueckkehr zum Verwaltungsmenue
    verwalte_optionen_menu();
}

//==================================================================================================

// Ruft Screen zum Anzeigen der Optionen auf
void optionen_ausgeben_bild()
{
    // Leert den Bildschirm
    leere_bild();

    // Ruft Funktion zum Anzeigen der Optionen auf
    ausgeben_optionen_liste();

    // Warte auf Eingabe
    warte_auf_eingabe();

    // Rueckkehr zum Verwaltungsmenue
    verwalte_optionen_menu();
}

//==================================================================================================

// Ruft Screen zum Speichern der Optionen auf
void optionen_speichern_bild()
{
    // Leert den Bildschirm
    leere_bild();

    // Ruft Funktion zum Speichern der Optionen auf
    speichern_optionen_datei();

    // Rueckkehr zum Verwaltungsmenue
    verwalte_optionen_menu();
}

//==================================================================================================

// Ruft Screen zum Beenden des Programms auf
void programm_beenden_bild()
{
    // leer den Bildschirm
    leere_bild();

    // Nutzerabfrage ob Programm wirklich beendet werden soll
    if (auswahl_jn("Moechten Sie das Programm wirklich beenden?"))
    {
        // Beendet das Programm
        exit(0);
    }
    else
    {
        // Rueckkehr zum Hauptmenue
        haupt_menu();
    }
}

//==================================================================================================