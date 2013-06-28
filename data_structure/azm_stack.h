//azm_stack.h
#ifndef AZM_STACK_H_
#define AZM_STACK_H_

#include"azm_list.h"

typedef struct azm_stack_s{
    azm_list_t  list;

    /*************************************
    *       this example show you how
    *    to use inheritance-like style in c
    *         other varibales
    *
    **************************************/

    //size_t obj_size;


} azm_stack_t;

void azm_stack_init(azm_stack_t *stack, void (*destroy)(void *));
void azm_stack_destroy(azm_stack_t *stack);


int azm_stack_push(azm_stack_t *stack, const void *data);
int azm_stack_pop(azm_stack_t *stack, void **data);

#define azm_stack_peek(stack) (((azm_list_t *)(stack))->head == NULL ? NULL : (((azm_list_t *))(stack))->head->data)

#define azm_stack_size(stack) (((azm_list_t *)(stack))->size)

#endif // AZM_STACK_H_INCLUDED
