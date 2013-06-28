//azm_list.c
#include<string.h>
#include"azm_list.h"


void azm_list_init(azm_list_t * list, void (*destroy)(void *))
{
    list->size = 0;
    list->destroy = destroy;

    list->head = NULL;
    list->tail = NULL;

    return ;
}


void azm_list_destroy(azm_list_t * list)
{
    void *data;
    while(azm_list_size(list) > 0){
        if(azm_list_rem_next(list, NULL, (void **)&data) == 0
           && list->destroy != NULL){

               list->destroy(data);
        }
    }

    memset(list, 0, sizeof(azm_list_t));
    return ;
}


int azm_list_ins_next(azm_list_t *list, azm_list_elmt_t *elmt, const void *data)
{
    azm_list_elmt_t * new_elmt;

    if( (new_elmt = (azm_list_elmt_t*) malloc(sizeof(azm_list_elmt_t))) == NULL ){

            return -1;
    }

    new_elmt->data = (void*)data;


    if(elmt == NULL){
        /*handle insert into list head*/
        if(azm_list_size(list) == 0)
            list->tail = new_elmt;
        new_elmt->next = list->head;
        list->head = new_elmt;

    }
    else {
        //handle insert into tail
        if(elmt->next == NULL)
            list->tail = new_elmt;
        new_elmt->next = elmt->next;
        elmt->next = new_elmt;
    }

    list->size++;

    return 0;
}

int azm_list_rem_next(azm_list_t *list, azm_list_elmt_t *elmt, void **data)
{
    azm_list_elmt_t * old_elmt;

    if(list->size == 0)
        return -1;

    if(elmt == NULL){

        old_elmt = list->head;
        list->head = list->head->next;

        if(list->size == 1)
            list->tail = NULL;

    }
    else {

        if(elmt->next == NULL)
            return -1;
        old_elmt = elmt->next;
        elmt->next = elmt->next->next;

        if(elmt->next == NULL)
            list->tail = elmt;
    }

    *data = old_elmt->data;
    free(old_elmt);
    list->size--;

    return 0;
}
