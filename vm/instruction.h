//
// Created by Fin on 04.11.2018.
//

#ifndef VM_INSTRUCTION_H

#define VM_INSTRUCTION_H

struct frame;

typedef enum {
    ALOAD,
    ILOAD,

    ICONST,
    ISTORE,

    INVOKEVIRTUAL,

    IADD,

    RETURN,
    IRETURN
} type_instruction;


typedef struct {
    type_instruction type;
    int number_line;
    int arg;
    struct frame *frame_arg;
} instruction;

void execute(struct frame*, instruction*);

#endif //VM_INSTRUCTION_H