#include "Instruction.h"
#include "frame.h"


void iconst(Frame *frame, int arg) {
    frame->pointerStack++;
    frame->stack[frame->pointerStack] = arg;
}

void istore(Frame *frame, int indexLocalPool) {
    frame->localPool[indexLocalPool] = frame->stack[frame->pointerStack];
    frame->pointerStack--;
}

void iload(Frame *frame, int indexLocalPool) {
    frame->pointerStack++;
    frame->stack[frame->pointerStack] = frame->localPool[indexLocalPool];
}

void iadd(Frame *frame) {
    frame->stack[frame->pointerStack - 1] = frame->stack[frame->pointerStack] + frame->stack[frame->pointerStack - 1];
    frame->pointerStack--;
}

void invokeVirtual(Frame *frame, Frame *newFrame) {
    go(newFrame);
}

//int ireturn(Frame *frame) {
//    int ret = frame->stack[frame->pointerStack];
//    frame->pointerStack--;
//    return ret;
//}

void execute(Frame *frame, Instruction *instruction) {
    switch (instruction->type) {
        case ICONST:
            iconst(frame, instruction->arg);
            break;
        case ISTORE:
            istore(frame, instruction->arg);
            break;
//        case ALOAD:
//            break;
        case ILOAD:
            iload(frame, instruction->arg);
            break;
        case INVOKEVIRTUAL:
            invokeVirtual(frame, instruction->frameArg);
            break;
        case IADD:
            iadd(frame);
            break;
//        case RETURN:
//            break;
//        case IRETURN:
//            break;
    }
}