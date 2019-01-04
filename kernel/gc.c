//
// Created by fin on 04.01.19.
//
#include <stdlib.h>
#include "gc.h"

gc_t *gc;

int new(class_t *class) {
    gc->objects = realloc(gc->objects, sizeof(class_t));
    gc->objects[gc->number_objects++] = class;
    return (int) gc->objects[gc->number_objects - 1];
}
