//azm_set.c
#include<string.h>
#include"azm_set.h"

void azm_set_init(azm_set_t *set, void (*destroy)(void *), int (*cmp)(const void *, const void *))
{
    azm_list_init(set, destroy);
    set->cmp = cmp;
    return ;
}

int azm_set_insert(azm_set_t *set, const void *data)
{
    if(azm_set_is_member(set, data))
        return 1;

    return azm_list_ins_next(set, NULL, data);
}


int azm_set_remove(azm_set_t *set, void **data)
{
    azm_list_elmt_t *cur_iter;
    azm_list_elmt_t *prev_iter = NULL;

    for(cur_iter = azm_list_head(set); cur_iter != NULL; cur_iter = azm_list_next(cur_iter)){

        if(set->cmp(*data, azm_list_data(cur_iter)) == 0){
           break;
        }

        prev_iter = cur_iter;
    }

    if(cur_iter == NULL)
        return -1;

    return azm_list_rem_next(set, prev_iter, data);
}

int azm_set_union(azm_set_t *setu, const azm_set_t *set1, const  azm_set_t *set2)
{
    azm_list_elmt_t *mebr_iter;
    void *data;

    azm_set_init(setu, NULL, set1->cmp);

    for(mebr_iter = azm_list_head(set1); mebr_iter != NULL; mebr_iter = azm_list_next(mebr_iter)){

        data = azm_list_data(mebr_iter);
        if(azm_list_ins_next(setu, azm_list_tail(setu), data) != 0){
            azm_set_destroy(setu);
            return -1;
        }
    }

    for(mebr_iter = azm_list_head(set2); mebr_iter != NULL; mebr_iter = azm_list_next(mebr_iter)){

        if(azm_set_is_member(set1, azm_list_data(mebr_iter))){
            continue;
        }
        else {

            data = azm_list_data(mebr_iter);
            if(azm_list_ins_next(setu, azm_list_tail(setu), data ) != 0){
                azm_set_destroy(setu);
                return -1;
            }
        }

    }

    return 0;
}

int azm_set_intersection(azm_set_t *seti, const azm_set_t *set1, const  azm_set_t *set2)
{
    azm_list_elmt_t *mebr_iter;
    void *data;

    azm_set_init(seti, NULL, set1->cmp);

    for(mebr_iter = azm_list_head(set1); mebr_iter != NULL; mebr_iter = azm_list_next(mebr_iter)){

        if(azm_set_is_member(set2, azm_list_data(mebr_iter))){
             data = azm_list_data(mebr_iter);
            if(azm_list_ins_next(seti, azm_list_tail(seti), data) != 0){

                azm_set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}


int azm_set_difference(azm_set_t *setd, const azm_set_t *set1, const  azm_set_t *set2)
{

    azm_list_elmt_t *mebr_iter;
    void *data;

    azm_set_init(setd, NULL, set1->cmp);

    for(mebr_iter = azm_list_head(set1); mebr_iter != NULL; mebr_iter = azm_list_next(mebr_iter)){

        if(!azm_set_is_member(set2, azm_list_data(mebr_iter))){

            data = azm_list_data(mebr_iter);
            if(azm_list_ins_next(setd, azm_list_tail(setd), data) != 0){

                azm_set_destroy(setd);
                return -1;
            }
        }
    }

    return 0;
}

int azm_set_is_member(const azm_set_t *set, const void *data)
{
    azm_list_elmt_t *mebr_iter;

    for(mebr_iter = azm_list_head(set); mebr_iter != NULL; mebr_iter = azm_list_next(mebr_iter)){

        if(set->cmp(data, azm_list_data(mebr_iter)) == 0){
            return 1;
        }
    }

    return 0;
}



int azm_set_is_subset(const azm_set_t *set1, const  azm_set_t *set2)
{
    azm_list_elmt_t *mebr_iter;

    if(azm_set_size(set1) > azm_set_size(set2))
        return 0;

     for(mebr_iter = azm_list_head(set1); mebr_iter != NULL; mebr_iter = azm_list_next(mebr_iter)){

        if(!azm_set_is_member(set2, azm_list_data(mebr_iter))){
            return 0;
        }
    }

    return 1;


}

int azm_set_is_equal(const azm_set_t *set1, const azm_set_t *set2)
{
    if(azm_set_size(set1) == azm_set_size(set2))
        return azm_set_is_subset(set1, set2);

    return 0;

}
