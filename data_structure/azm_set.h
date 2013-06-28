//azm_set.h
#ifndef _AZM_SET_H_
#define _AZM_SET_H_

#include"azm_list.h"

typedef azm_list_t azm_set_t;

void azm_set_init(azm_set_t *set, void (*destroy)(void *), int (*cmp)(const void *, const void *));

#define azm_set_destroy azm_list_destroy

int azm_set_insert(azm_set_t *set, const void *data);
int azm_set_remove(azm_set_t *set, void **data);
int azm_set_union(azm_set_t *setu, const azm_set_t *set1, const  azm_set_t *set2);
int azm_set_intersection(azm_set_t *seti, const azm_set_t *set1, const  azm_set_t *set2);
int azm_set_difference(azm_set_t *setd, const azm_set_t *set1, const  azm_set_t *set2);

int azm_set_is_member(const azm_set_t *set, const void *data);

#define azm_set_is_include azm_set_is_member

int azm_set_is_subset(const azm_set_t *set1, const  azm_set_t *set2);
int azm_set_is_equal(const azm_set_t *set1, const  azm_set_t *set2);


#define azm_set_size(set) ((set)->size)


#endif
