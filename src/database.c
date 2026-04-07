#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/wordle.h"

/* ── Vérifie qu'un token est exactement WORD_LEN lettres minuscules ── */
static int is_valid_word(const char *token) {
    if ((int)strlen(token) != WORD_LEN) return 0;
    for (int i = 0; i < WORD_LEN; i++)
        if (!islower((unsigned char)token[i])) return 0;
    return 1;
}

/* ── Charge tous les mots depuis le fichier texte ── */
/* Stratégie :
   - On ne lit que les lignes indentées (espaces/tab) → listes de mots
   - On s'arrête après avoir traité la ligne contenant "zonal" (dernier mot)
   Retourne le nombre de mots chargés, ou -1 en cas d'erreur.              */
int load_words(const char path[], char words[][WORD_LEN + 1]) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Erreur : impossible d'ouvrir le fichier de mots");
        return -1;
    }

    int   count = 0;
    int   done  = 0;
    char  line[1024];

    while (!done && fgets(line, sizeof(line), fp)) {
        /* Lignes non indentées = titres / texte → on ignore */
        if (line[0] != ' ' && line[0] != '\t') continue;

        /* Fin de la section des mots : la ligne contient "zonal" */
        if (strstr(line, "zonal")) done = 1;

        char *token = strtok(line, " \t\n\r");
        while (token != NULL) {
            if (is_valid_word(token) && count < MAX_WORDS) {
                strncpy(words[count], token, WORD_LEN);
                words[count][WORD_LEN] = '\0';
                count++;
            }
            token = strtok(NULL, " \t\n\r");
        }
    }

    fclose(fp);
    return count;
}

/* ── Vérifie si un mot est présent dans le tableau ── */
int is_in_list(const char word[], const char words[][WORD_LEN + 1], int count) {
    for (int i = 0; i < count; i++)
        if (strcmp(word, words[i]) == 0) return 1;
    return 0;
}
