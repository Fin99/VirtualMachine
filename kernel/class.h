//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_CLASS_H
#define VIRTUALMACHINE_CLASS_H

typedef struct class class_t;
struct class{
    int index_class;
    char* name;

    int number_fields;
};

typedef struct object object_t;
struct object{
    class_t *class;

    int* fields;
};

void destructor_class(class_t *class);

void destructor_object(object_t *object);
#endif //VIRTUALMACHINE_CLASS_H
