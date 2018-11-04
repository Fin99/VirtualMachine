//
// Created by Fin on 04.11.2018.
//
#include "VM.h"

int main() {
    frame.pointerStack = -1;

}

//stack work
void constt(int constt) {
    frame.pointerStack++;
    frame.stack[frame.pointerStack] = constt;
}

void store(int indexLocalPool) {
    frame.localPool[indexLocalPool] = frame.stack[frame.pointerStack];
    frame.pointerStack--;
}

void load(int indexLocalPool) {
    frame.pointerStack++;
    frame.stack[frame.pointerStack] = frame.localPool[indexLocalPool];
}

//operation
void add(){
    frame.stack[frame.pointerStack-1] = frame.stack[frame.pointerStack] + frame.stack[frame.pointerStack-1];
    frame.pointerStack--;
}
//other
int ireturn() {
    int ret = frame.stack[frame.pointerStack];
    frame.pointerStack--;
    return ret;
}