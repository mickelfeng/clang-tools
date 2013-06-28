

#include <stdlib.h>

#ifndef AZM_HEAP_H
#define AZM_HRAP_H

typedef struct azm_heap_ {
    int size;
    int (*cmp) (const void *, const void *);
    void (*destroy)(void *);

    void **tree;
} azm_heap;

void azm_heap_init(
            azm_heap*heap,
            int (*cmp)(const void *, const void *),
            void (*destroy)(void *));

void azm_heap_dealloc(azm_heap *heap);

int azm_heap_insert(azm_heap *heap, const void *data);

int azm_heap_extract(azm_heap *heap, void **data);

#define azm_heap_size(heap) ((heap)->size)


#endif

