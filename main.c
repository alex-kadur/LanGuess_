#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// each of our text files contains 50 words
#define LISTSIZE 50

// values for colors and score
// EXACT == right letter, right place;
// CLOSE == right letter, wrong place;
// WRONG == wrong letter
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"

// user-defined function prototypes
void get_wordsize(int *wordsize);
int get_choice(int wordsize, char choice[]);
void get_guess(char guess[], int wordsize);
int check_word(char guess[], int wordsize, int status[], char choice[]);
void print_word(char guess[], int wordsize, int status[]);
void print_result(bool won, char choice[]);

int main(void)
{
    // prompt for wordsize and ...
    // ... store intput in wordsize
    int wordsize;
    get_wordsize(&wordsize);

    // open correct file, ...
    // ... load words from file into array and ...
    // ... pseudorandomly select 1 word
    char choice[wordsize + 1];
    if (get_choice(wordsize, choice))
    {
        printf("Error opening file %d.txt\n", wordsize);
        return 1;
    }

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;

    // determines outcome of the game
    // eventually set to true if guess correct
    // game is lost if main loop ends anf won is false
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN "This is WORDLE50" RESET "\n\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of ...\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // get user's guess
        char guess[wordsize + 1];
        get_guess(guess, wordsize);

        // array to hold guess status
        int status[wordsize];

        // initially sets all elements of status array initially to 0 (WRONG)
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        // calculate score for guess
        int score = check_word(guess, wordsize, status, choice);

        // print guess
        printf("Guess %i: ", i + 1);
        print_word(guess, wordsize, status);

        // if guess is exactly right ...
        // ... set won to true and ...
        // ... terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // print the game's result
    print_result(won, choice);

    return 0;
}

// prompt for wordsize and ...
// ... ensure it is either 5, 6, 7, or 8
// store provided value in 'wordsize'
void get_wordsize(int *wordsize)
{
    do
    {
        printf("Choose a wordsize (5, 6, 7, or 8): ");
        scanf("%d", wordsize);

        if (*wordsize < 5 || *wordsize > 8)
        {
            printf("Wordsize must be either 5, 6, 7, or 8!\n");
        }

    } while (*wordsize < 5 || *wordsize > 8);
    system("clear");
}

// open correct file, ...
// ... load words from file into array and ...
// ... pseudorandomly select 1 word
int get_choice(int wordsize, char choice[])
{
    // open correct file
    char filename[6];
    sprintf(filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(filename, "r");
    if (wordlist == NULL)
    {
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];
    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    strcpy(choice, options[rand() % LISTSIZE]);

    return 0;
}

// store user input in guess array
void get_guess(char guess[], int wordsize)
{
    // ensure users actually provide a guess that is the correct length
    do
    {
        printf("\nInput a %i-letter word: ", wordsize);
        scanf("%s", guess);
    } while (wordsize != strlen(guess));
}

// compare guess to choice and score points as appropriate, storing points in status
int check_word(char guess[], int wordsize, int status[], char choice[])
{
    int score = 0;

    for (int i = 0; i < wordsize; i++)
    {
        if (guess[i] == choice[i])
        {
            status[i] = 2;
            score += 2;
            continue;
        }
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[j])
            {
                status[i] = 1;
                score += 1;
                continue;
            }
        }
    }

    return score;
}

// print word character-for-character with correct color coding, then reset terminal font to normal
void print_word(char guess[], int wordsize, int status[])
{
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == 2)
        {
            printf(GREEN "%c" RESET, guess[i]);
        }
        else if (status[i] == 1)
        {
            printf(YELLOW "%c" RESET, guess[i]);
        }
        else
        {
            printf(RED "%c" RESET, guess[i]);
        }
    }
    printf("\n");
    return;
}

// Print the game's result
void print_result(bool won, char choice[])
{
    if (won)
    {
        printf("\n" GREEN "You won!" RESET "\n\n\n");
    }
    else
    {
        printf("\n" RED "GAME OVER" RESET "\n");
        printf("\nThe target word was: %s\n\n\n", choice);
    }
}
