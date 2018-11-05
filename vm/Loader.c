//
// Created by Fin on 04.11.2018.
//
#include "Loader.h"
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

void createInstruction(const char *string, Instruction instruction) {

    char **splitString = NULL;
    split(string, ':', &splitString);

    puts(splitString[0]);
    puts(splitString[1]);
}

int createInstructions(char **stringSplit, int numberString, int numberStringNameFrame, Instruction **instructions) {
    int counter = 0;
    if (numberString == numberStringNameFrame) {
        return 0;
    }
    for (int i = numberStringNameFrame + 1; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ') {
            break;
        } else {
            counter++;
        }
    }

    *instructions = malloc(sizeof(Instruction) * counter);
    int numberInstructions = 0;

    for (int i = numberStringNameFrame + 1; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ') {
            break;
        } else {
            createInstruction(string, (*instructions)[numberInstructions]);
            numberInstructions++;
        }
    }
    return counter;
}

int createFrames(char **stringSplit, int numberString, Frame **frames) {
    int counter = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ') {
            counter++;
        }
    }

    *frames = malloc(sizeof(Frame) * counter);

    int counterFrames = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ') {
            (*frames)[counterFrames].name = string;
            counterFrames++;
            Instruction *instructions = NULL;
            i += createInstructions(stringSplit, numberString, i, &instructions);
            (*frames)[counterFrames].instructions = instructions;
        }
    }
    return counter;
}

int main() {
    const char *fileToString = readFile("byte.fn");

    char **stringSplit = NULL;
    int numberString = split(fileToString, '\n', &stringSplit);

    Frame *frames = NULL;

    int numberFrames = createFrames(stringSplit, numberString, &frames);

    puts(frames[1].name);

    return 0;
}

