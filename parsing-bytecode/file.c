//
// Created by Fin on 15.11.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

char *read_file(const char *file_name) {
    char *file_as_string = NULL;
    FILE *file = fopen(file_name, "r");

    if (file != NULL) {
        if (fseek(file, 0L, SEEK_END) == 0) {
            long buf_size = ftell(file);
            if (buf_size == -1) { return NULL; }

            file_as_string = malloc(sizeof(char) * (buf_size + 1));

            if (fseek(file, 0L, SEEK_SET) != 0) {
                return NULL;
            }

            size_t new_len = fread(file_as_string, sizeof(char), (size_t) buf_size, file);
            if (new_len == 0) {
                fputs("Error reading file", stderr);
            } else {
                file_as_string[new_len] = '\0';
            }
        } else {
            return NULL;
        }
        fclose(file);
    } else {
        return NULL;
    }
    return file_as_string;
}
