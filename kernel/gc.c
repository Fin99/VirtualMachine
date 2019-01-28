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
    gc = malloc(sizeof(gc_t));

    gc->objects = NULL;
    gc->number_objects = 0;
    gc->heap_size = 0;
}

int get_index_object(object_t *object){
    for (int i = 0; i < gc->number_objects; ++i) {
        if(object == gc->objects[i]){
            return i;
        }
    }
    return 0; //error
}

void start_gc() {
    bool *mark = malloc(sizeof(bool) * gc->number_objects);
    for (int k = 0; k < gc->number_objects; ++k) {
        mark[k] = false;
    }

    frame_t **frames = get_stack_frame()->frames;
    long long number_frames = get_stack_frame()->number_frames;

    for (int i = 0; i < number_frames; ++i) {
        frame_t *frame = frames[i];
        for (int j = 0; j < frame->index_first_element_work_stack; ++j) {
            if (frame->is_work_stack_element_object[j]) {
                int index = get_index_object((object_t *)frame->work_stack[j]);
                mark[index] = true;
            }
        }

        for (int j = 0; j < LOCAL_POOL_SIZE_MAX; ++j) {
            if (frame->is_local_pool_element_object[j]) {
                int index = get_index_object((object_t *)frame->local_pool[j]);
                mark[index] = true;
            }
        }
    }

    if(DEBUG || DEBUG_HEAP){
        puts("Snap root");
        for (int i = 0; i < gc->number_objects; ++i) {
            printf("%i: %p - %s\n", i, gc->objects[i], mark[i]?"true":"false");
        }
    }
    free(mark);
}

bool check_gc(class_t *class) {
    long long size_object = sizeof(object_t) + sizeof(long long) * class->number_fields;

    if (true) {//todo size_object + gc->heap_size > MAX_HEAP_SIZE * 0.8
        start_gc();
    }

    if (size_object + gc->heap_size > MAX_HEAP_SIZE) {
        return false;
    }

    if(DEBUG || DEBUG_HEAP){
        printf("Max heap size: %i. Heap size: %lli. Load: %lli%%\n", MAX_HEAP_SIZE,
               gc->heap_size, (gc->heap_size + size_object) * 100 / MAX_HEAP_SIZE);
    }

    return true;
}

long long new_object(class_t *class) {
    if (check_gc(class)) {
        gc->objects = realloc(gc->objects, (size_t) ((gc->number_objects + 1) * 8));
        gc->heap_size += sizeof(object_t) + sizeof(long long) * class->number_fields;

        object_t *object = constructor_object(class);

        gc->objects[gc->number_objects++] = object;
        return (long long) object;
    } else {
        return (long long) NULL; //error
    }
}
