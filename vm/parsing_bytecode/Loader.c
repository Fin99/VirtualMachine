//
// Created by Fin on 04.11.2018.
//
#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STACK 128
#define SIZE_LOCAL_POOL 128


int main() {
    const char *fileToString = readFile("byte.fn");

    char **stringSplit = NULL;
    int numberString = split(fileToString, '\n', &stringSplit);

    Frame *frames = NULL;

    int numberFrames = createFrames(stringSplit, numberString, &frames);

    for (int i = 0; i < numberFrames; ++i) {
        printf("%i:\n", i);
        printf("Name - %s\n", frames[i].name);
        printf("InstructionSize - %i\n", frames[i].instructionsSize);
        Frame frame = frames[i];
        for (int j = 0; j < frames[i].instructionsSize; ++j) {
            printf("\t%i: %i - %i, %p\n", frame.instructions[j].numberLine, frame.instructions[j].type,
                    frame.instructions[j].arg, frame.instructions[j].frameArg);
        }
    }

    Frame *main = NULL;
    for (int i = 0; i < numberFrames; ++i) {
        if (!strcmp("main()", frames[i].name)) {
            main = &frames[i];
        }
    }
    go(main);

    printf("%i", main->stack[frames->pointerStack]);
    return 0;
}

int createFrames(char **fileSplit, int numberString, Frame **frames) {
    int counter = countingFrames(fileSplit, numberString);

    *frames = malloc(sizeof(Frame) * counter);

    for (int j = 0; j < counter; ++j) {
        frames[j]->stack = malloc(sizeof(int) * SIZE_STACK);

        frames[j]->locaPoolSize = SIZE_LOCAL_POOL;
        frames[j]->localPool = malloc(sizeof(int) * SIZE_LOCAL_POOL);

        frames[j]->pointerStack = -1;
    }

    setFramesName(fileSplit, numberString, frames);

    int counterFrames = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(fileSplit + i);
        if (*string != ' ') {
            Instruction *instructions = NULL;
            int numberInstructions = createInstructions(fileSplit, numberString, i, &instructions, *frames);
            i += numberInstructions;
            (*frames)[counterFrames].instructions = instructions;
            (*frames)[counterFrames].instructionsSize = numberInstructions;

            counterFrames++;
        }
    }
    return counter;
}

int countingFrames(char **fileSplit, int numberString) {
    int counter = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(fileSplit + i);
        if (*string != ' ') {
            counter++;
        }
    }

    return counter;
}

void setFramesName(char **fileSplit, int numberString, Frame **frames) {
    int counterFrames = 0;
    for (int i = 0; i < numberString; ++i) {
        char *string = *(fileSplit + i);
        if (*string != ' ') {
            (*frames)[counterFrames].name = string;
            counterFrames++;
        }
    }
}

int createInstructions(char **stringSplit, int numberString, int numberStringNameFrame, Instruction **instructions,
                       Frame *frames) {
    int counterInstruction = 0;
    if (numberString == numberStringNameFrame) {
        return 0;
    }
    for (int i = numberStringNameFrame + 1; i < numberString; ++i) {
        char *string = *(stringSplit + i);
        if (*string != ' ') {
            break;
        } else {
            counterInstruction++;
        }
    }

    *instructions = malloc(sizeof(Instruction) * counterInstruction);
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
    return counterInstruction;
}

void setNumberLineInstruction(const char *string, Instruction *instruction) {

    char **splitString = NULL;
    split(string, ':', &splitString);

    instruction->numberLine = (int) strtol(splitString[0], NULL, 10);
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
        ptr->arg = (int) strtol(splitString2[1], NULL, 10);
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
        ptr->arg = (int) strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "return")) {
        ptr->type = RETURN;
    } else if (!strcmp(splitString2[0], "iconst")) {
        ptr->type = ICONST;
        ptr->arg = (int) strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "iload")) {
        ptr->type = ILOAD;
        ptr->arg = (int) strtol(splitString2[1], NULL, 10);
    } else if (!strcmp(splitString2[0], "ireturn")) {
        ptr->type = IRETURN;
    } else if (!strcmp(splitString2[0], "iadd")) {
        ptr->type = IADD;
    }
}

