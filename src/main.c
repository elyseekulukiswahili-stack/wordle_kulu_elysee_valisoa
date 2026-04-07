#include <stdio.h>
#include <stdlib.h>
#include "../include/wordle.h"

int main(void) {
    /* ── Chargement de la base de données ── */
    static char words[MAX_WORDS][WORD_LEN + 1];
    int count = load_words(DICT_PATH, words);

    if (count <= 0) {
        fprintf(stderr, "Erreur : aucun mot charge depuis %s\n", DICT_PATH);
        return EXIT_FAILURE;
    }

    printf("Base de donnees chargee : %d mots disponibles.\n", count);

    /* ── Boucle de parties ── */
    int rejouer = 1;
    while (rejouer)
        rejouer = play_game(words, count);

    printf("Merci d'avoir joue ! A bientot.\n");
    return EXIT_SUCCESS;
}
