#ifndef STICK_H_INCLUDED
#define STICK_H_INCLUDED

#include <stdlib.h>
#include<stdbool.h>
typedef struct spt_sticks_s {
    int quantity; //木棍总数量
    int count; //统计当前数量
    int sum; //统计总长度
    bool *visited; //标记是否已经成功配对
    int *sticks; //保存木棍的长度
}spt_sticks_t ;

int spt_sticks_init(spt_sticks_t * spt_s, int stick_quantity);
void spt_sticks_destroy(spt_sticks_t * spt_s);
int spt_sticks_append_stick(spt_sticks_t * spt_s, int stick_len);
int spt_sticks_get_min_origin(spt_sticks_t * spt_s);


#endif // STICK_H_INCLUDED
