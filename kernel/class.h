//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_CLASS_H
#define VIRTUALMACHINE_CLASS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct class class_t;
struct class {
    int index_class;
    char *name;

    int number_fields;
};

typedef struct object object_t;
struct object {
    class_t *class;

    int64_t *fields;

    bool *is_field_object;
};

class_t *constructor_class(int index_class, char *class_name, int number_field);

void destructor_class(class_t *class);

object_t *constructor_object(class_t *class);

void destructor_object(object_t *object);

#endif //VIRTUALMACHINE_CLASS_H
