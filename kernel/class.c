//
// Created by fin on 04.01.19.
//

#include <stdlib.h>
#include "class.h"

struct class *constructor_class(int index_class, char *class_name, int number_field){
    struct class *class = malloc(sizeof(struct class));

    class->index_class = index_class;
    class->name = class_name;
    class->number_fields = number_field;

    return class;
}

void destructor_class(struct class *class) {
    free(class->name);
    free(class);
}

struct object *constructor_object(struct class *class) {
    struct object *object = malloc(sizeof(struct object));
    object->fields = malloc(sizeof(int64_t) * class->number_fields);
    object->is_field_object= calloc(1, sizeof(bool) * class->number_fields);
    object->class = class;
    return object;
}

void destructor_object(struct object *object) {
    free(object->fields);
    free(object->is_field_object);
    free(object);
}