//
// Created by Fin on 04.11.2018.
//

#ifndef VM_LOADER_H
#define VM_LOADER_H

#include "../Frame.h"
#include "String.h"
#include "File.h"

void loadByteCode();

int createFrames(char **fileSplit, int numberString, Frame **frames);

int countingFrames(char **fileSplit, int numberString);

void setFramesName(char **fileSplit, int numberString, Frame **frames);

int createInstructions(char **stringSplit, int numberString, int numberStringNameFrame, Instruction **instructions,
                       Frame *frames);

void setNumberLineInstruction(const char *string, Instruction *instruction);

void setTypeInstruction(char *string, Instruction *ptr, Frame *frames);

#endif //VM_LOADER_H
