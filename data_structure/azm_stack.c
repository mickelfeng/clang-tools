//azm_stack.c

#include"azm_stack.h"

void azm_stack_init(azm_stack_t *stack, void (*destroy)(void *))
{

    azm_list_init((azm_list_t *)stack, destroy);
    //do other thing

}
void azm_stack_destroy(azm_stack_t *stack)
{
    azm_list_destroy((azm_list_t *)stack);
    //do other thing
}

int azm_stack_push(azm_stack_t *stack, const void *data)
{
    if(azm_list_ins_next((azm_list_t *)stack, NULL, data) != 0){
        return -1;
    }
    //do other thing
    return 0;

}

int azm_stack_pop(azm_stack_t *stack, void **data)
{
    if(azm_list_rem_next((azm_list_t *)stack, NULL, data) != 0){
        return -1;
    }
    //do other thing
    return 0;
}
