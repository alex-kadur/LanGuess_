#include <stdio.h>

void ausgabe_linie(int lenght);
void leere_eingabepuffer(void);
int neue_runde(char *text);
void umwandlung_kleinbuchstaben(char eingabe[]);
void leere_screen(void);

//======================================================//

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

void leere_eingabepuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//======================================================//

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

void leere_screen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
