//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_CLASS_H
#define VIRTUALMACHINE_CLASS_H

#include <stdbool.h>
#include <stdint.h>
#include "frame.h"

struct class {
    int index_class;
    char *name;

    int number_fields;
};

struct object {
    struct class *class;

    var *fields;

    bool *is_field_object;
};

struct class *constructor_class(int index_class, char *class_name, int number_field);

void destructor_class(struct class *class);

struct object *constructor_object(struct class *class);

void destructor_object(struct object *object);

#endif //VIRTUALMACHINE_CLASS_H
