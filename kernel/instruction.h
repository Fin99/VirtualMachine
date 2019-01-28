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
    long long index_instruction;

    type_instruction_t type_instruction;

    long long *args;
};

void execute_instruction(instruction_t instruction);

instruction_t *constructor_instruction(long long index, type_instruction_t type, long long *args);

void destructor_instruction(instruction_t *instruction);

#endif //VM_INSTRUCTION_H