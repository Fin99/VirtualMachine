#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "gc.h"
#include "stack_frame.h"

gc_t *gc = NULL;

void destructor_gc() {
    for (long long i = 0; i < gc->number_objects; ++i) {
        destructor_object(gc->objects[i]);
    }
    free(gc->objects);
    free(gc);
}

void init_gc() {
    if (gc != NULL) {
        destructor_gc();
    }
    gc = malloc(sizeof(gc));

    gc->objects = NULL;
    gc->number_objects = 0;
    gc->heap_size = 0;
}

void start_gc() {

}

object_t *create_object(class_t *class) {
    object_t *object = malloc(sizeof(object_t));
    object->fields = malloc(sizeof(long long) * class->number_fields);
    object->class = class;
    return object;
}

bool check_gc(class_t *class) {
    long long size_object = sizeof(object_t) + sizeof(long long) * class->number_fields;

    if (size_object + gc->heap_size > MAX_HEAP_SIZE * 0.8) {
        start_gc();
    }

    if (size_object + gc->heap_size > MAX_HEAP_SIZE) {
        return false;
    }

    if(DEBUG || DEBUG_HEAP){
        printf("Max heap size: %i. Heap size: %lli. Load: %lli%%\n", MAX_HEAP_SIZE, gc->heap_size, (gc->heap_size+size_object)*100/MAX_HEAP_SIZE);
    }

    return true;
}

long long new_object(class_t *class) {
    if (check_gc(class)) {
        gc->objects = realloc(gc->objects, sizeof(object_t *));
        gc->heap_size += sizeof(object_t) + sizeof(long long) * class->number_fields;

        object_t *object = create_object(class);

        gc->objects[gc->number_objects] = object;
        return (long long) object;
    } else {
        return (long long) NULL;
    }
}
