//
// Created by Fin on 15.11.2018.
//

#include <stdlib.h>
#include <memory.h>
#include "string.h"

void destructor_split_string(char **split_str, size_t size) {
    for (int i = 0; i < size; ++i) {
        free(split_str[i]);
    }

    free(split_str);
}

char **split(const char *str, const char *delimiter, size_t *size) {
    char *str_cpy = malloc(strlen(str) + 1);
    strcpy(str_cpy, str);
    *size = 0;

    char **split_str = NULL;
    char *part = strtok(str_cpy, delimiter);

    while (part != NULL) {
        (*size)++;

        split_str = realloc(split_str, (8 * (*size)));
        split_str[(*size) - 1] = malloc(strlen(part) + 1);

        strcpy(split_str[(*size) - 1], part);

        part = strtok(NULL, delimiter);
    }

    free(str_cpy);

    return split_str;
}