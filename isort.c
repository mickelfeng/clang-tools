//
//  isort.c
//  insert sort algorithm
//
//  Created by Thomas Huang on 12-3-16.
//  Copyright (c) 2012??? __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if __STDC_VERSION__ >= 199901L
        #include <stdbool.h>
        #define C99
#else
        typedef enum {false, true} bool;
#endif

int integercompare(const void * dataPrev, const void * dataPost );

bool isort(void * data, int length, int elementSize, int (*cmp)(const void *,const void *));

#define repr_array(arr,  len) {\
                int i = 0;\
                        fprintf(stdout, "Array :[");\
                        for(; i < len-1 ; i++){\
                                fprintf(stdout, " %03d,", arr[i] );\
                        }\
                fprintf(stdout, "%03d ]\n", arr[i] );}
                        
int main (int argc, const char * argv[])
{
    // insert code here...
    int arr[10] = {10, 5, 23, 56, 34, 78, 68, 54, 37, 98};
    int *p = arr; 
    puts("Before sort:");
        repr_array(arr, 10);
    
        
    isort(p, 10, sizeof(int),  &integercompare);
    puts("After sort:");
    repr_array(arr, 10);
  
    return 0;
}


int integercompare(const void * dataPrev, const void * dataPost )
{
    const int *data1_int = ((const int*)dataPrev);
    const int *data2_int = ((const int*)dataPost);
    //printf("%5d, %5d\n", *data1_int, *data2_int);
    return ((*data1_int) > (*data2_int)) - ((*data1_int) < (*data2_int));
}

bool isort(void * data, int length, int elementSize, int (*cmp)(const void *, const void *))
{
    char *a = data;
    void *iter;
    
        int i , j;
    
    if((iter = (char *)malloc(elementSize)) == NULL)
        return false;
    
    if(data == NULL )
        return false;
    
    for( i = 1; i < length; i++ ) {
        memcpy(iter,  a + i * elementSize , elementSize);
        j = i -1;
        
        while(j >= 0 && cmp(data + j * elementSize , iter) > 0){
            
            memcpy(a + (j + 1) * elementSize, a + j * elementSize , elementSize);
            j--;
        }
        
        if(j != (i - 1))
            memcpy(a + (j + 1) * elementSize, iter, elementSize);
    }
    free(iter);
    return true;
}

