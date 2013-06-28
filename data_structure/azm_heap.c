
#include <stdlib.h>
#include <string.h>
#include "azm_heap.h"

#define heap_parent(index) ((int)(((index) - 1) / 2))

#define heap_left(index) (((index) * 2) + 1)

#define heap_right(index) (((index) * 2) + 2)


void heap_init(
            Heap *heap,
            int (*cmp)(const void *, const void *),
            void (*destroy)(void *))
{
    heap->size = 0;
    heap->cmp = cmp;
    heap->destroy = destroy;
    heap->tree = NULL;
    return ;
}



void heap_dealloc(Heap *heap)
{
    int i;
    if(heap->destroy != NULL) {
        for(i = 0; i < heap_size(heap); i++) {
                heap->destroy(heap->tree[i]);
        }
    }

    free(heap->tree);

    memset(heap, 0, sizeof(Heap));
    return ;
}

int heap_insert(Heap *heap, const void *data)
{
    void *tmp;
    int iindex, //
        pindex; //parent index
    if((tmp = (void **) realloc(heap->tree,
            (heap_size(heap) + 1) * sizeof(void *))) == NULL) {
            return -1;
    }
    else {
     heap->tree = tmp;
    }
    heap->tree[heap_size(heap)] = (void *) data;
    iindex = heap_size(heap);
    pindex = heap_parent(iindex);
    while(iindex > 0 &&
          heap->cmp(heap->tree[pindex], heap->tree[iindex]) < 0) {

        tmp = heap->tree[pindex];
        heap->tree[pindex] = heap->tree[iindex];
        heap->tree[iindex] = tmp;
        iindex = pindex;
        pindex = heap_parent(iindex);
    }

    heap->size++;

    return 0;
}

int heap_extract(Heap *heap, void **data)
{
    void *save;
    void *tmp;

    int iindex,
        lindex,
        rindex,
        mindex;

    if(heap_size(heap) == 0)
        return -1;
    *data = heap->tree[0];
    save = heap->tree[heap_size(heap) - 1];

    if (heap_size(heap) - 1 > 0) {
        if((tmp = (void **) realloc(heap->tree,
            (heap_size(heap) - 1) * sizeof(void *))) == NULL) {
            return -1;
        }
        else {
        heap->tree = tmp;
        }
        heap->size--;
    }
    else {

        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    heap->tree[0] = save;
    iindex = 0;
    while(1) {
        lindex = heap_left(iindex);
        rindex = heap_right(iindex);

        if(lindex < heap_size(heap) &&
           heap->cmp(heap->tree[lindex], heap->tree[iindex]) > 0) {
            mindex = lindex;
        }
        else {
            mindex = iindex;
        }

        if(rindex < heap_size(heap) &&
           heap->cmp(heap->tree[rindex], heap->tree[mindex]) > 0) {
            mindex = rindex;
        }


        if(mindex == iindex) {
            break;
        }
        else {

            tmp = heap->tree[mindex];
            heap->tree[mindex] = heap->tree[iindex];
            heap->tree[iindex] = tmp;
            iindex = mindex;
        }
    }

    return 0;
}
