#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/wordle.h"

void check_guess(const char guess[], const char target[], char result[]) {

    for (int i = 0; i < WORD_LEN; i++)
        result[i] = LETTER_WRONG;
    result[WORD_LEN] = '\0';


    int used[WORD_LEN] = {0};


    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == target[i]) {
            result[i] = LETTER_CORRECT;
            used[i]   = 1;
        }
    }


    for (int i = 0; i < WORD_LEN; i++) {
        if (result[i] == LETTER_CORRECT) continue; 
        for (int j = 0; j < WORD_LEN; j++) {
            if (!used[j] && guess[i] == target[j]) {
                result[i] = LETTER_MISPLACED;
                used[j]   = 1;
                break;
            }
        }
    }
}


int play_game(const char words[][WORD_LEN + 1], int count) {

    srand((unsigned int)time(NULL));
    const char *target = words[rand() % count];

    char guess[64];
    char result[WORD_LEN + 1];
    int  tries    = 0;
    int  won      = 0;

    printf("\n--- Nouveau Wordle ---\n");
    printf("Devinez un mot de 5 lettres. Vous avez %d essais.\n\n", MAX_TRIES);

    while (tries < MAX_TRIES && !won) {

        printf("Proposer un mot: ");
        if (!fgets(guess, sizeof(guess), stdin)) break;


        guess[strcspn(guess, "\n")] = '\0';
        to_lower_str(guess);


        if ((int)strlen(guess) != WORD_LEN) {
            printf("Le mot doit faire exactement %d lettres.\n\n", WORD_LEN);
            continue;
        }


        if (!is_in_list(guess, words, count)) {
            printf("Mot invalide (absent du dictionnaire), reessayez.\n\n");
            continue;
        }

        tries++;
        check_guess(guess, target, result);
        print_result(guess, result);
        printf("\n");

 
        if (strcmp(guess, target) == 0) {
            won = 1;
            printf("Bravo, vous avez gagne en %d coup%s !\n", tries, tries > 1 ? "s" : "");
        }
    }


    if (!won)
        printf("Dommage ! Le mot etait : %s\n", target);


    printf("\nVoulez-vous rejouer ? (o/n) : ");
    char answer[8];
    if (!fgets(answer, sizeof(answer), stdin)) return 0;
    to_lower_str(answer);
    return (answer[0] == 'o');
}
