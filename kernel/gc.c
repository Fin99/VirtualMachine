#include <stdlib.h>
#include "gc.h"

gc_t *gc = NULL;

void destructor_gc() {
    for (int i = 0; i < gc->number_objects; ++i) {
        destructor_object(gc->objects[i]);
    }
    free(gc->objects);
    free(gc);
}

void init_stack_frame() {
    if (gc != NULL) {
        destructor_gc();
    }
    gc = malloc(sizeof(gc));

    gc->objects = NULL;
    gc->number_objects = 0;
}

int new_object(class_t *class) {
    gc->objects = realloc(gc->objects, sizeof(object_t *));

    object_t *object = malloc(sizeof(object_t));
    object->class = class;
    object->fields = malloc(sizeof(int) * class->number_fields);

    gc->objects[gc->number_objects] = object;
    return (int) object;
}
