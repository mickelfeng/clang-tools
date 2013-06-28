
#include"qksort.h"

static int partition(
            void *data,
            int esize,
            int i,
            int k,
            int (*cmp)(const void *, const void *))
{
    char *array = data;
    void *pval,
         *tmp;

    int randi[3];
    int choice;

    int n,m;

    if((pval = malloc(esize)) == NULL)
        return -1;
    if((tmp = malloc(esize)) == NULL){
        free(pval);
         return -1;
    }

    randi[0] = (rand() % (k - i + 1) ) + i;
    randi[1] = (rand() % (k - i + 1) ) + i;
    randi[2] = (rand() % (k - i + 1) ) + i;

    //another sort algorithm (insert sort)
    for(m = 1; m < 3; m++){

        n = m;
        choice = randi[n];
        while(n > 0 && randi[n-1] > choice  ){

            randi[n] = randi[n - 1];
            n--;
        }
        randi[n] = choice;
    }

    memcpy(pval, &array[randi[1]*esize], esize);

    i--, k++;
    while(1){

        do{
            k--;
        } while(cmp(&array[k*esize], pval) > 0);

        do{
            i++;
        } while(cmp(&array[i*esize], pval) < 0);

        if( i >= k){
            break;
        }
        else {

            memcpy(tmp,&array[i*esize], esize);
            memcpy(&array[i*esize],&array[k*esize], esize);
            memcpy(&array[k*esize],tmp, esize);
        }
    }

    free(pval), free(tmp);

    return k;
}

int qksort(
           void *data,
           int len,
           int esize,
           int i,
           int k,
           int (*cmp)(const void *, const void *))
{
    int j;

    while(i < k){

        if( (j = partition(data,esize, i, k, cmp )) < 0)
            return -1;
        if(qksort(data, len, esize, i, j, cmp) < 0)
            return -1;
        i = j + 1;
    }

    return 0;
}
