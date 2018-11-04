//
// Created by Fin on 04.11.2018.
//

#ifndef VM_VM_H
#define VM_VM_H

#endif //VM_VM_H

struct Frame {
    int stack[50];
    int localPool[50];
    int pointerStack;
}frame;

//stack work
void constt(int constt);

void store(int indexLocalPool);

void load(int indexLocalPool);

//operation
void add();
//other
int ireturn();