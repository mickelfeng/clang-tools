//azm_queue.c

#ifndef _AZM_QUEUE_H_
#define _AZM_QUEUE_H

#include"azm_list.h"

typedef azm_list_t azm_queue_t;

#define azm_queue_init azm_list_init
#define azm_queue_destroy azm_list_destroy

int azm_queue_enqueue(azm_queue_t *queue, const void *data);
int azm_queue_dequeue(azm_queue_t *queue, void **data);


#define azm_queue_size azm_list_size
#define azm_queue_is_empty(queue) (azm_queue_size(queue) == 0 ? 1 : 0)
#define azm_queue_peek(queue) ((queue)->head == NULL? NULL : (queue)->head->data)



#endif // _AZM_QUEUE_H_
