//
// Created by Fin on 04.11.2018.
//

#ifndef VM_INSTRUCTION_H

#define VM_INSTRUCTION_H

#include "frame.h"

enum type_instruction {
    ADD,
    DIV_I,
    MUL,

    COMPARE,

    IF_ACMPEQ,
    IF_ACMPNE,
    GOTO,

    NEW,
    GET_FIELD,
    SET_FIELD,

    LOAD,
    CONST,
    STORE,
    POP,
    CLEAR_LOCAL_VARIABLE,

    INVOKE,

    RETURN,
    I_RETURN,
    O_RETURN
};

struct instruction {
    int index_instruction;

    enum type_instruction type_instruction;

    void *args;
};

int *execute_instruction(struct instruction instruction);

struct instruction *constructor_instruction(int index, enum type_instruction type, void *args);

void destructor_instruction(struct instruction *instruction);

#endif //VM_INSTRUCTION_H