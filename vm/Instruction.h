//
// Created by Fin on 04.11.2018.
//

#ifndef VM_INSTRUCTION_H

#define VM_INSTRUCTION_H

struct Frame;

typedef enum {
    ALOAD,
    ILOAD,
    ICONST,
    ISTORE,
    INVOKEVIRTUAL,
    RETURN,
    IRETURN
} TypeInstruction;


typedef struct {
    TypeInstruction type;
    long numberLine;
    long arg;
    struct Frame *frameArg;
} Instruction;

void execute(struct Frame);

#endif //VM_INSTRUCTION_H