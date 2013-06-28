
#include"kmp.h"
#include<stdio.h>


static int  bord_table(const char *pat, int *bord)
{
     int t = -1,
         j;

    int *temp_bord;
    if(pat == NULL)
        return -1;

    int len = strlen(pat);
    if( (temp_bord = (int *)malloc((len+1)*sizeof(int))) == NULL)
        return -1;
    temp_bord[0] = -1;
    for(j = 0; j < len; j++){
        while(t >= 0 && pat[t] != pat[j]){

            t = temp_bord[t];
        }

        t++;
        temp_bord[j + 1] = t;

    }


    memcpy(bord, temp_bord + 1, len*sizeof(int));
    free(temp_bord);
    return 0;
}

static int  strong_bord_table(const char *pat, int *strong_bord)
{
     int t = -1,
         j;
    int *temp_bord;
    if(pat == NULL)
        return -1;

    int len = strlen(pat);
    if( (temp_bord = (int *)malloc((len+1)*sizeof(int))) == NULL)
        return -1;

    temp_bord[0] = -1;
    for(j = 0; j < len; j++){
        while(t >= 0 && pat[t] != pat[j]){

            t = temp_bord[t];
        }
        t++;

        if(j == len -1 || pat[t] != pat[j+1] ){
            temp_bord[j+1] = t;
        }
        else {
            temp_bord[j + 1] = temp_bord[t];
        }

    }


    memcpy(strong_bord, temp_bord + 1, len*sizeof(int));
    free(temp_bord);
    return 0;

}

int mp(const char *text,const char *pat)
{
    int *bord;
    int n , m;
    int i = 0, j  = 0;
    n = strlen(text);
    m = strlen(pat);


    if((bord = (int *)malloc(m*sizeof(int))) == NULL)
        return -1;

    bord_table(pat, bord);
    while(i < n - m){

        while(j < m && pat[j] == text[i+j]){
            j = j +1;

        }

        if(j == m) {
            free(bord);
            return i;

            }

        i = i + j - bord[j];
        j = (bord[j] > 0)? bord[j] : 0;
    }

    free(bord);
    return -1;
}

int kmp(const char *text,const char *pat)
{
    int *strong_bord;
    int  n , m;
    int i = 0, j  = 0;
    n = strlen(text);
    m = strlen(pat);




    if((strong_bord = (int *)malloc(m*sizeof(int))) == NULL)
        return -1;

    strong_bord_table(pat, strong_bord);
    while(i < n - m){

        while(j < m && pat[j] == text[i+j]){
            j = j +1;

        }

        if(j == m) {
            free(strong_bord);
            return i;

            }

        i = i + j - strong_bord[j];
        j = (strong_bord[j] > 0)? strong_bord[j] : 0;

    }

    free(strong_bord);
    return -1;
}


#define REHASH(a, b, h) ((((h)- (a) * d) << 1) + (b))

int krap_rabin(const char *text, const char *pat)
{
    int j = 0, d= 1;
    int text_h = 0, pat_h = 0;
    int n, m;
    n = strlen(text);
    m = strlen(pat);
    d = d << (m -1);
    for(; j < m ; j++){
        pat_h = ((pat_h << 1) + pat[j]);
        text_h = ((text_h << 1) + text[j]);
    }

    j = 0;
    while(j < n - m) {
        if(pat_h == text_h)
            printf("find %s in [%d]\n", pat ,j);

        text_h = REHASH(text[j], text[j + m], text_h );
        j++;
    }

    return 0;

}


static void BmBc(const char *pat, int len, char *bmbc)
{

    int i = 0;

    for(; i < 256; i++){

    }
}

