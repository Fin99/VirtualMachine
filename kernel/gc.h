//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_GC_H
#define VIRTUALMACHINE_GC_H

#include "class.h"

typedef struct gc gc_t;
struct gc{
    object_t **objects;
    int number_objects;
};

int new_object(class_t *class);
#endif //VIRTUALMACHINE_GC_H
