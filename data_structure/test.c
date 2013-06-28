//
//  this simple data structure algorithm
//
//
//  Created by Thomas Huang(������) on 12-12-16.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

#include"azm_stack.h"

void print(const void *data)
{
    fprintf(stdout, "iter(integer) : %5d\n", *(int *)data);
}

void azm_stack_print(azm_stack_t *stack, void (*print)(const void *))
{
    azm_list_elmt_t *elmt_iter;
    fprintf(stdout, "Stack info:\n");
    fprintf(stdout, "stack size: %d\n", azm_stack_size(stack));
    for(elmt_iter = azm_list_head((azm_list_t *)stack); elmt_iter != NULL; elmt_iter = elmt_iter->next){
        //printf("iter %p\n", elmt_iter);
        print(azm_list_data(elmt_iter));
    }

    fprintf(stdout, "\n");

}

int main()
{
    int *data;
    int i,
        randint;
    azm_stack_t stack;
    azm_stack_init(&stack, free);
    srand(time(NULL));

    for(i = 0; i < 10; i++){

        randint = rand() % 100;
        if((data = (int *)malloc(sizeof(int))) == NULL){
            perror("data malloc failed:");
            return 0;
        }

        memcpy(data, &randint, sizeof(int));

       if( azm_stack_push(&stack, data) != 0) {
            fprintf(stderr, "stack push data %5d failed\n", *data);
            return 0;
       }

    }

    fprintf(stdout, "After stack push  data:\n\n");
    azm_stack_print(&stack, print);
    for(i = 0; i < 5; i++){

       if( azm_stack_pop(&stack ,(void **)&data) != 0) {
            fprintf(stderr, "stack pop data  failed\n");
            return 0;
       }

       fprintf(stdout, "stack pop data %5d\n", *data);
       free(data);
    }

    fprintf(stdout, "\nAfter stack pop data:\n\n");
    azm_stack_print(&stack, print);
    azm_stack_destroy(&stack);

    return 0;
}
