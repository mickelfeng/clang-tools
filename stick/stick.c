#include<string.h>
#include"stick.h"



static int int_cmp(const void * a, const void * b){
    return (*((int *)a)) < (*((int *)b));
}

static int spt_sticks_search(const spt_sticks_t * spt_s,int current_len, int start, int cnt , int goal_len){
//宏的意义在于：定义常量、补充C语言的泛型特性、增强代码可读性、不重复原则，即减少重复。
#define check_stick_visited(i, spt_sticks) ((spt_sticks)->visited[i] && \
                (i && !(spt_sticks)->visited[i] && (spt_sticks)->visited[i - 1] == (spt_sticks)->visited[i]))
    int i;

    if (spt_s->sum == cnt * goal_len)
        return 1;
    for (i = start; i < spt_s->quantity; i++){

        //检查木棍是否已经被标记，另外重复长度的木棍可以跳过
        if(check_stick_visited(i, spt_s))
            continue;

        if(current_len + spt_s->sticks[i] == goal_len) {
            spt_s->visited[i] = true;

            if(spt_sticks_search(spt_s, 0, 0, cnt + 1, goal_len))
                return 1;
            spt_s->visited[i] = false;
            if(current_len == 0) return 0;
        }
        else if(current_len + spt_s->sticks[i] < goal_len){
            spt_s->visited[i] = true;
            if(spt_sticks_search(spt_s, current_len + spt_s->sticks[i], i + 1, cnt + 1, goal_len))
                return 1;
            spt_s->visited[i] = false;
            if(current_len == 0)
                return 0;
        }
    }
    return 0;
#undef check_stick_visited
}


int spt_sticks_init(spt_sticks_t * spt_s, int stick_quantity){

    //木棍范围控制
    if (stick_quantity < 0 || stick_quantity > 64)
        return 0;

    if ((spt_s->sticks = (int *)malloc(sizeof(int) * stick_quantity)) == NULL)
        return -1;

    //释放已分配的存木棍长度数组的内存
    if((spt_s->visited = (bool *)malloc(sizeof(bool) * stick_quantity)) == NULL){
        free(spt_s->sticks);
        return -1;
    }


    spt_s->count = 0;
    spt_s->sum = 0;
    spt_s->quantity = stick_quantity;
    memset(spt_s->visited, false, sizeof(bool) * spt_s->quantity);
    memset(spt_s->sticks, 0 , sizeof(int) * stick_quantity);
    return 1;
}


void spt_sticks_destroy(spt_sticks_t * spt_s){

    if (spt_s->sticks)
        free(spt_s->sticks);
    free(spt_s->visited);
    memset(spt_s, 0 , sizeof(spt_sticks_t));
    return;
}

int spt_sticks_append_stick(spt_sticks_t * spt_s, int stick_len){

    int ret = 0;
    if((stick_len > 0 && stick_len <= 5) && (spt_s->count < spt_s->quantity)) {
        spt_s->sticks[spt_s->count++] = stick_len;
        spt_s->sum += stick_len;
        ret = 1;
    }
    return ret;
}

int spt_sticks_get_min_origin(spt_sticks_t * spt_s){

    int goal_len;
    //排序成长度递减，加快遍历搜索。
    qsort(spt_s->sticks, spt_s->count, sizeof(int), int_cmp);
    for(goal_len = spt_s->sticks[0]; goal_len < spt_s->sum; goal_len++) {
        if(spt_s->sum % goal_len != 0)
            continue;
        memset(spt_s->visited, false, sizeof(bool) * spt_s->quantity);
        if(spt_sticks_search(spt_s, 0, 0, 0, goal_len))
            break;
    }
    return goal_len;
}
