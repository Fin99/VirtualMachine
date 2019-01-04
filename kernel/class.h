//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_CLASS_H
#define VIRTUALMACHINE_CLASS_H

typedef struct class class_t;
struct class {
    long long index_class;
    char *name;

    long long number_fields;
};

typedef struct object object_t;
struct object {
    class_t *class;

    long long *fields;
};

void destructor_class(class_t *class);

void destructor_object(object_t *object);

#endif //VIRTUALMACHINE_CLASS_H
