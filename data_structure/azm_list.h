//azm_list.h
#ifndef _AZM_LIST_H_
#define _AZM_LIST_H_

#include<stdlib.h>

typedef struct azm_list_elmt_s azm_list_elmt_t;

struct azm_list_elmt_s
{
    void *data;
    azm_list_elmt_t *next;
};

typedef struct azm_list_s
{
    int size;

    int (*cmp) (const void *, const void *);
    void (*destroy)(void *);

    azm_list_elmt_t *head;
    azm_list_elmt_t *tail;

} azm_list_t;

void azm_list_init(azm_list_t * list, void (*destroy) (void *));
void azm_list_destroy(azm_list_t * list);
int azm_list_ins_next(azm_list_t *list, azm_list_elmt_t *elmt, const void *data);
int azm_list_rem_next(azm_list_t *list, azm_list_elmt_t *elmt, void **data);


#define azm_list_size(list) ((list)->size)
#define azm_list_head(list) ((list)->head)
#define azm_list_tail(list) ((list)->tail)

#define azm_list_is_head(list, elmt) ((list)->head == (elmt)? 1 : 0)
#define azm_list_is_tail(elmt) ((elmt)->next == NULL ? 1 : 0)
#define azm_list_data(elmt) ((elmt)->data)
#define azm_list_next(elmt) ((elmt)->next)


#endif
