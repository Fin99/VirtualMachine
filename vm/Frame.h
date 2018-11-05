//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

struct Instruction;

typedef struct {
    char *name;
    int *stack;
    int *localPool;
    int pointerStack;
    struct Instruction *instructions;
} Frame;
#endif //VM_FRAME_H
