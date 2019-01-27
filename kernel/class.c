//
// Created by fin on 04.01.19.
//

#include <stdlib.h>
#include "class.h"

void destructor_class(class_t *class) {
    free(class->name);
}

object_t *constructor_object(class_t *class) {
    object_t *object = malloc(sizeof(object_t));
    object->fields = malloc(sizeof(long long) * class->number_fields);
    object->is_field_object= malloc(sizeof(bool) * class->number_fields);
    object->class = class;
    return object;
}

void destructor_object(object_t *object) {
    free(object->fields);
    free(object->is_field_object);
    free(object);
}