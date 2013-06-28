//azm_queue.c

#include"azm_queue.h"

int azm_queue_enqueue(azm_queue_t *queue, const void *data)
{
        return azm_list_ins_next(queue, azm_list_tail(queue), data);
}

int azm_queue_dequeue(azm_queue_t *queue, void **data)
{
    return azm_list_rem_next(queue, NULL, data);
}
