//
// Created by Fin on 04.11.2018.
//
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    i = strlen(s) - 1;
    while ((s[i] == ' ') || (s[i] == '\t')) {
        i--;
    }
    if (i < (strlen(s) - 1)) {
        s[i + 1] = '\0';
    }
}

void setTypeInstruction(char *string, Instruction *ptr, Frame *frames) {
    char **splitString = NULL;
    split(string, ':', &splitString);
    trim(splitString[1]);

    char **splitString1 = NULL;
    split(splitString[1], ' ', &splitString1);

    char **splitString2 = NULL;
    split(splitString1[0], '_', &splitString2);

    if (!strcmp(splitString2[0], "aload")) {
        ptr->type = ALOAD;
        ptr->arg = strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "invokevirtual")) {
        ptr->type = INVOKEVIRTUAL;
        int i = 0;
        while (1) {
            if (!strcmp(frames[i].name, splitString1[1])) {
                ptr->frameArg = &frames[i];
                break;
            }
            i++;
        }
    } else if (!strcmp(splitString2[0], "istore")) {
        ptr->type = ISTORE;
        ptr->arg = strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "return")) {
        ptr->type = RETURN;
    } else if (!strcmp(splitString2[0], "iconst")) {
        ptr->type = ICONST;
        ptr->arg = strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "iload")) {
        ptr->type = ILOAD;
        ptr->arg = strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "ireturn")) {
        ptr->type = IRETURN;
    }
    printf("%li ", ptr->numberLine);
    printf("%d ", ptr->type);
    printf("%li ", ptr->arg);
    printf("%p\n", ptr->frameArg);
}

void setNumberLineInstruction(const char *string, Instruction *instruction) {

    char **splitString = NULL;
    split(string, ':', &splitString);

    instruction->numberLine = strtol(splitString[0], NULL, 10);
}

int createInstructions(char **stringSplit, int numberString, int numberStringNameFrame, Instruction **instructions,
                       Frame *frames) {
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
            setNumberLineInstruction(string, &(*instructions)[numberInstructions]);
            setTypeInstruction(string, &(*instructions)[numberInstructions], frames);
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
        }
    }

    counterFrames = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ') {
            Instruction *instructions = NULL;
            i += createInstructions(stringSplit, numberString, i, &instructions, *frames);
            (*frames)[counterFrames].instructions = instructions;

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

    int numberFrames = createFrames(stringSplit, numberString, &frames);

    return 0;
}

