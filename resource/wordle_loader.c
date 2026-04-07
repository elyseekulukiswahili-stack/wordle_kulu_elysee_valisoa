#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS     3000
#define WORD_LENGTH   5

/* Retourne 1 si le token est exactement 5 lettres minuscules */
int is_valid_word(const char *token) {
    if (strlen(token) != WORD_LENGTH)
        return 0;
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!islower((unsigned char)token[i]))
            return 0;
    }
    return 1;
}

/* Retourne 1 si la ligne commence par un espace ou une tabulation
   (les listes de mots dans le fichier sont toutes indentées) */
int is_indented(const char *line) {
    return (line[0] == ' ' || line[0] == '\t');
}

int main(void) {
    /* ── Ouverture du fichier ── */
    FILE *fp = fopen("bdd_wordle.txt", "r");
    if (!fp) {
        perror("Erreur : impossible d'ouvrir bdd_wordle.txt");
        return EXIT_FAILURE;
    }

    /* ── Tableau de mots ── */
    char words[MAX_WORDS][WORD_LENGTH + 1];
    int  count = 0;

    char line[1024];
    int  done = 0;  /* flag : on a fini la section des mots */
    while (!done && fgets(line, sizeof(line), fp)) {
        /* On ne traite QUE les lignes indentées (= listes de mots) */
        if (!is_indented(line))
            continue;

        /* La dernière ligne de mots contient "zonal" ; après ça on arrête */
        if (strstr(line, "zonal"))
            done = 1;

        char *token = strtok(line, " \t\n\r");
        while (token != NULL) {
            if (is_valid_word(token) && count < MAX_WORDS) {
                strncpy(words[count], token, WORD_LENGTH);
                words[count][WORD_LENGTH] = '\0';
                count++;
            }
            token = strtok(NULL, " \t\n\r");
        }
    }
    fclose(fp);

    /* ── Affichage du résultat ── */
    printf("Nombre de mots charges : %d\n\n", count);
    for (int i = 0; i < count; i++) {
        printf("[%4d] %s\n", i + 1, words[i]);
    }

    return EXIT_SUCCESS;
}

