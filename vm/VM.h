//
// Created by Fin on 04.11.2018.
//

#ifndef VM_VM_H
#define VM_VM_H

#include "Frame.h"

#endif //VM_VM_H

//stack work
void constt(int constt);

void store(int indexLocalPool);

void load(int indexLocalPool);

//operation
void add();

//other
int ireturn();

void invokeVirtual(Frame frame, int *const isResult, int *const result) {
    Frame newFrame;
    for (int i = 0; frame.pointerStack > -1; frame.pointerStack--) {
        newFrame.localPool[i++] = frame.stack[frame.pointerStack];
    }
    //todo
}