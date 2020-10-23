//
// Created by Fin on 15.11.2018.
//

#include <stdlib.h>
#include <ctype.h>
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



size_t trim(char *out, size_t len, const char *str) {
    if(len == 0)
        return 0;

    const char *end;
    size_t out_size;

    // Trim leading space
    while(isspace(*str)) str++;

    if(*str == 0)  // All spaces?
    {
        *out = 0;
        return 1;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    end++;

    // Set output size to minimum of trimmed string length and buffer size minus 1
    out_size = (end - str) < len-1 ? (end - str) : len-1;

    // Copy trimmed string and add null terminator
    memcpy(out, str, out_size);
    out[out_size] = 0;

    return out_size;
}