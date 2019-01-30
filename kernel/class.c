//
// Created by fin on 04.01.19.
//

#include <stdlib.h>
#include "class.h"

class_t *constructor_class(long long index_class, char *class_name, long long number_field){
    class_t *class = malloc(sizeof(class_t));

    class->index_class = index_class;
    class->name = class_name;
    class->number_fields = number_field;

    return class;
}

void destructor_class(class_t *class) {
    free(class->name);
    free(class);
}

object_t *constructor_object(class_t *class) {
    object_t *object = malloc(sizeof(object_t));
    object->fields = malloc(sizeof(long long) * class->number_fields);
    object->is_field_object= calloc(1, sizeof(bool) * class->number_fields);
    object->class = class;
    return object;
}

void destructor_object(object_t *object) {
    free(object->fields);
    free(object->is_field_object);
    free(object);
}