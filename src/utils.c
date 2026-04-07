#include <stdio.h>
#include <ctype.h>
#include "../include/wordle.h"

void to_lower_str(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = (char)tolower((unsigned char)s[i]);
}

void print_result(const char guess[], const char result[]) {
    printf("%s\n", guess);
    printf("%s\n", result);
}
