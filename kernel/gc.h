//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_GC_H
#define VIRTUALMACHINE_GC_H

#include "class.h"

typedef struct gc gc_t;
struct gc{
    class_t **objects;
    int number_objects;
};

int new(class_t *class);
#endif //VIRTUALMACHINE_GC_H
