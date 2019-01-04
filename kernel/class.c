//
// Created by fin on 04.01.19.
//

#include <stdlib.h>
#include "class.h"

void destructor_class(class_t *class){
    free(class->name);
}

void destructor_object(object_t *object){
    free(object->fields);
    free(object);
}