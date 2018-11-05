//
// Created by Fin on 04.11.2018.
//
#include "Loader.h"
#include "Frame.h"
#include <stdio.h>
#include <stdlib.h>

const char *readFile(const char *const filename) {
    char *source = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long bufsize = ftell(fp);
            if (bufsize == -1) { /* Error */ }

            source = malloc(sizeof(char) * (bufsize + 1));

            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Handle error here */ }

            size_t newLen = fread(source, sizeof(char), bufsize, fp);
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

int split(const char *str, char c, char ***arr) {
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
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
            (*arr)[i] = (char *) malloc(sizeof(char) * token_len);
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char *) malloc(sizeof(char) * token_len);
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
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

int createFrame(char **stringSplit, int numberString, Frame **frames) {
    int counter = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ' && *string != '\r') {
            counter++;
        }
    }

    *frames = malloc(sizeof(Frame) * counter);

    int counterFrames = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ' && *string != '\r') {
            (*frames)[counterFrames].name = string;
            counterFrames++;
        }
    }
    return counter;
}

int main() {
    const char *fileToString = readFile("byte.fn");

    char **stringSplit = NULL;
    int numberString = split(fileToString, '\n', &stringSplit);

    Frame *frames = NULL;

    int numberFrames = createFrame(stringSplit, numberString, &frames);

    puts(frames[0].name);
}

