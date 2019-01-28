//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_GC_H
#define VIRTUALMACHINE_GC_H

#include "class.h"

#define MAX_HEAP_SIZE 4096

typedef struct gc gc_t;
struct gc {
    object_t **objects;
    long long number_objects;
    long long heap_size;
};

gc_t *get_gc();

void destructor_gc();

long long new_object(class_t *class);

void init_gc();

#endif //VIRTUALMACHINE_GC_H
