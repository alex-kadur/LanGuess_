void ausgabe_linie(int lenght);
void leere_eingabepuffer(void);
int neue_runde(char *text);
void umwandlung_kleinbuchstaben(char eingabe[]);
void leere_screen(void);

//======================================================//

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

//======================================================//

// Leert den Eingabepuffer
void leere_eingabepuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//======================================================//

// Gibt String entsprechend Uebergabewert aus
// Fordert Nutzer zur Eingabe (j/n) auf
// Rueckgabewert 1 falls 'j' oder 'J'
// Sonst Rueckgabewert 0
int neue_runde(char *text)
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

//======================================================//

// Wandelt Zeichen im Uebergabe-Array von Gross- zu Kleinbuchstaben um
void umwandlung_kleinbuchstaben(char input[])
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        // check if the character is an uppercase letter
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            // convert to lowercase by adding 32 to the ASCII value
            input[i] = input[i] + 32;
        }
    }
}

//======================================================//

// Leert den Bildschirm unabhaengig vom Betriebssystem
void leere_screen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//======================================================//

// Wartet auf Nutzereingabe
void warte_auf_eingabe(void)
{
    printf("\nWeiter mit Enter ...");
    leere_eingabepuffer();    
}

//======================================================//