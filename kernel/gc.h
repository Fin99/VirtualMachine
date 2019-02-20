//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_GC_H
#define VIRTUALMACHINE_GC_H

#include "class.h"

#define MAX_HEAP_SIZE 4096

struct gc {
    struct object **objects;
    uint64_t number_objects;
    uint64_t heap_size;
};

struct gc *get_gc();

void destructor_gc();

void start_gc();

uint64_t new_object(struct class *class);

void init_gc();

#endif //VIRTUALMACHINE_GC_H
