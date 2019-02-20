//
// Created by Fin on 04.11.2018.
//

#ifndef VM_INSTRUCTION_H

#define VM_INSTRUCTION_H

typedef enum type_instruction type_instruction_t;
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

typedef struct instruction instruction_t;
struct instruction {
    int index_instruction;

    type_instruction_t type_instruction;

    int64_t *args;
};

int *execute_instruction(instruction_t instruction);

instruction_t *constructor_instruction(int index, type_instruction_t type, int64_t *args);

void destructor_instruction(instruction_t *instruction);

#endif //VM_INSTRUCTION_H