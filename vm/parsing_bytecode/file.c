//
// Created by Fin on 15.11.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

const char *read_file(const char *const file_name) {
    char *source = NULL;
    FILE *fp = fopen(file_name, "r");
    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long buf_size = ftell(fp);
            if (buf_size == -1) { /* Error */ }

            source = malloc(sizeof(char) * (buf_size + 1));

            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Handle error here */ }

            size_t new_len = fread(source, sizeof(char), (size_t) buf_size, fp);
            if (new_len == 0) {
                fputs("Error reading file", stderr);
            } else {
                source[new_len] = '\0';
            }
        }
        fclose(fp);
    }
    return source;
}
