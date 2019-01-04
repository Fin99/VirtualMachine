//
// Created by fin on 04.01.19.
//

#ifndef VIRTUALMACHINE_CLASS_H
#define VIRTUALMACHINE_CLASS_H

typedef struct class class_t;
struct class{
    int index_class;
    char* name;

    int* fields;
    int number_fields;
};

void destructor_class(class_t *class);
#endif //VIRTUALMACHINE_CLASS_H
