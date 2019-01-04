//
// Created by Fin on 04.11.2018.
//

#ifndef VM_INSTRUCTION_H

#define VM_INSTRUCTION_H

typedef enum type_instruction type_instruction_t;
enum type_instruction {
    ADD,
    DIV,

    COMPARE,

    LOAD,
    CONST,
    STORE,

    INVOKE,

    RETURN,
    IRETURN
};

typedef struct instruction instruction_t;
struct instruction {
    int index_instruction;

    type_instruction_t type_instruction;

    int *args;
};

void execute_instruction(instruction_t instruction);

instruction_t* constructor_instruction(int index, type_instruction_t type, int *args);

#endif //VM_INSTRUCTION_H