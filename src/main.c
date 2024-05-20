#include "../include/data_operations.h"
#include "../include/ui.h"

//------------------MAIN------------------//

// Einstiegspunkt des Programms
int main()
{
    // Zeigt Titelbildschirm
    titel_bild();

    // Aktualisiert Optionenliste
    aktualisieren_optionen_liste();

    // Ruft Hauptmenue auf
    haupt_menu();

    // Gibt Optionenliste frei
    free_optionen_liste();

    // Beendet das Programm
    return 0;
}

//==================================================================================================