//
// Created by Fin on 15.11.2018.
//

#include <stdlib.h>
#include "string.h"
#include "string.h"

int split(const char *str, char c, char ***arr) {
    int count = 1;
    int token_len = 1;
    int i = 0;
    const char *p;
    char *t;

    p = str;
    while (*p != '\0') {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char **) malloc(sizeof(char *) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0') {
        if (*p == c) {
            (*arr)[i] = (char *) malloc(sizeof(char) * token_len - 1);
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char *) malloc(sizeof(char) * token_len - 1);
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0') {
        if (*p != c && *p != '\0') {
            *t = *p;
            t++;
        } else {
            if (*(t - 1) == '\r') {
                *(t - 1) = '\0';
            } else {
                *t = '\0';
            }
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

void trim(char *s) {
    // удаляем пробелы и табы с начала строки:
    int i = 0, j;
    while ((s[i] == ' ') || (s[i] == '\t')) {
        i++;
    }
    if (i > 0) {
        for (j = 0; j < strlen(s); j++) {
            s[j] = s[j + i];
        }
        s[j] = '\0';
    }

    // удаляем пробелы и табы с конца строки:
    i = (int) (strlen(s) - 1);
    while ((s[i] == ' ') || (s[i] == '\t')) {
        i--;
    }
    if (i < (strlen(s) - 1)) {
        s[i + 1] = '\0';
    }
}