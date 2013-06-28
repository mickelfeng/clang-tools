#include <stdio.h>
#include <stdlib.h>
#include"stick.h"



int main(int argc, char *argv[])
{
    int stick_quantity;
    spt_sticks_t sticks;
    int i;
    int stick_len;
    while(scanf("%d", &stick_quantity)){
        if(!stick_quantity) break;
        spt_sticks_init(&sticks, stick_quantity);
        i = 0;
        while(i < stick_quantity){
            scanf("%d", &stick_len );
            if(spt_sticks_append_stick(&sticks, stick_len) == 1)
                i++;
        }

        printf("%d\n", spt_sticks_get_min_origin(&sticks));
        spt_sticks_destroy(&sticks);
    }
    return 0;
}

