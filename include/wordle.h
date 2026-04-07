#ifndef WORDLE_H
#define WORDLE_H

/* ─── Constantes ─────────────────────────────────────────── */
#define WORD_LEN      5          /* longueur d'un mot Wordle   */
#define MAX_WORDS     3000       /* capacité du tableau de mots */
#define MAX_TRIES     6          /* nombre d'essais maximum     */
#define DICT_PATH     "resource/bdd_wordle.txt"

/* ─── Codes de résultat pour chaque lettre ──────────────── */
#define LETTER_WRONG     'x'    /* lettre absente du mot       */
#define LETTER_MISPLACED 'o'    /* présente mais mal placée    */
#define LETTER_CORRECT   'v'    /* bien placée                 */

/* ─── Prototypes ─────────────────────────────────────────── */

/* database.c */
int  load_words(const char path[], char words[][WORD_LEN + 1]);
int  is_in_list(const char word[], const char words[][WORD_LEN + 1], int count);

/* game.c */
void check_guess(const char guess[], const char target[], char result[]);
int  play_game(const char words[][WORD_LEN + 1], int count);

/* utils.c */
void to_lower_str(char *s);
void print_result(const char guess[], const char result[]);

#endif /* WORDLE_H */
