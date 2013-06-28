//
//  main.c
//  fib
//
//  Created by Thomas Huang on 12-3-17.
//  Copyright (c) 2012Äê__MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG


int fast_fib(int n, int * fib_array);
int fib(int n);
int fib1(int n, int fib_prev, int fib_post);

#ifdef DEBUG
    static int count = 0;
#endif

int main()
{
    int n = 30;
    fputs("Fibonacci -- cache version\n", stdout);

    fprintf(stdout, "fib(%d) is %5d\n", n, fib(n));

#ifdef DEBUG
    fprintf(stdout, "function called count : %d\n", count);
    count = 0;
#endif
    fputs("Fibonacci -- Tail recursion\n", stdout);
    fprintf(stdout, "fib(%d) is %5d\n", n, fib1(n, 1, 1));

#ifdef DEBUG
     fprintf(stdout, "function called count : %d\n", count);
#endif
    return 0;
}

int fast_fib(int n, int * fib_array)
{

    if( fib_array[n] == 0){
        fib_array[n] = fast_fib(n - 1, fib_array) + fast_fib(n - 2, fib_array);
    }

#ifdef DEBUG
    count++;
#endif
    return fib_array[n];
}

int fib(int n)
{
    int result = -1;

    // fib(n) -> fib_array[n]  cache to avoid  repeating the calculation of results
    int *fib_array;
    if(( fib_array = (int *)malloc( sizeof(int) * (n + 1) ) ) == NULL)
        return result;
    memset(fib_array, 0, sizeof(fib_array) * (n + 1));
    fib_array[0] = 1;
    fib_array[1] = 1;

    result = fast_fib(n, fib_array);
    free(fib_array);
    return result;
}


/*******************************************************************
*                                                                  *
*   fib(n, fib_prev, fib_post)  = fib_post when n in set{0, 1}     *
*   fib(n, fib_prev, fib_post) =                                   *
*      fib(n - 1, fib_post, fib_post + fib_prev )                  *
*      when n > 1                                                  *
*                                                                  *
********************************************************************/

// Fibonacci tail recursion
int fib1(int n, int fib_prev, int fib_post)
{
#ifdef DEBUG
    count++;
#endif
    if(n == 0 || n == 1) {
        return fib_post;
    } else {
        return fib1(n -1, fib_post , fib_post + fib_prev);
    }
}


