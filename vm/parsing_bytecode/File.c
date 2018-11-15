//
// Created by Fin on 15.11.2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "File.h"

const char *readFile(const char *const filename) {
    char *source = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long bufsize = ftell(fp);
            if (bufsize == -1) { /* Error */ }

            source = malloc(sizeof(char) * (bufsize + 1));

            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Handle error here */ }

            size_t newLen = fread(source, sizeof(char), (size_t) bufsize, fp);
            if (newLen == 0) {
                fputs("Error reading file", stderr);
            } else {
                source[newLen] = '\0';
            }
        }
        fclose(fp);
    }
    return source;
}
