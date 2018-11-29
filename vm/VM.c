//
// Created by Fin on 04.11.2018.
//
#include "VM.h"

//int main() {
//    frame.pointerStack = -1;
//
//}
//
////stack work
//void constt(int iconst) {
//    frame.pointerStack++;
//    frame.stack[frame.pointerStack] = iconst;
//}
//
//void istore(int indexLocalPool) {
//    frame.localPool[indexLocalPool] = frame.stack[frame.pointerStack];
//    frame.pointerStack--;
//}
//
//void iload(int indexLocalPool) {
//    frame.pointerStack++;
//    frame.stack[frame.pointerStack] = frame.localPool[indexLocalPool];
//}
//
////operation
//void iadd(){
//    frame.stack[frame.pointerStack-1] = frame.stack[frame.pointerStack] + frame.stack[frame.pointerStack-1];
//    frame.pointerStack--;
//}
////other
//int ireturn() {
//    int ret = frame.stack[frame.pointerStack];
//    frame.pointerStack--;
//    return ret;
//}