#include <stdio.h>
#include <stdlib.h>

//
//  Fibonacci.c
//  Fibonacci
//
//  Created by Thomas Huang on 12-4-05.
//  Copyright (c) 2012??1;?__MyCompanyName__. All rights reserved.
//

/*******************************************
*
*          matrix A =   [[1, 1],
*                        [1, 0]]
*          A^n = [[F(N+1), F(N)],
*                 [F(N),   F(N -1)]];
*
********************************************/
//

#define fib(n, power) \
    int F[2][2] = {{1,1},{1,0}};\
    if(n == 0)\
        return 0;\
    power(F, n-1);\
    return F[0][0];

void mul(int F[2][2], int M[2][2]);
void power1(int F[2][2], int n);
void power2(int F[2][2], int n);
int fib1(int n);
int fib2(int n);


int main()
{
    int n = 30;
    printf("Fibonacci(%03d) = %d\n", n, fib2(n));
    getchar();

    return 0;
}

void mul(int F[2][2], int M[2][2])
{
    // [[l: left, r : right],
    //  [t: top,  b : bootom]]
    int lt, rt,
        bl, br;

//  parallel setions by order {

    //parallel section 1 {
    lt = F[0][0]*M[0][0] + F[0][1]*M[1][0], rt =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
    bl = F[1][0]*M[0][0] + F[1][1]*M[1][0], br =  F[1][0]*M[0][1] + F[1][1]*M[1][1];
    //}
    //parallel section 2 {
    F[0][0] = lt, F[0][1] = rt;
    F[1][0] = bl, F[1][1] = br;
    //}
//}

}

// func : power1
// params :
// todo(matrix power)
// Time Complexity: O(n)
// Extra Space: O(1)
void power1(int F[2][2], int n)
{
    int i;
    int M[2][2] = {{1,1},{1,0}};

    for ( i = 2; i <= n; i++ )
        mul(F, M);

}

// func : power2
// params :
// todo(matrix power)
// Time Complexity: O(Logn)
// Extra Space: {'fuction stack size' : O(Logn),
//              'otherwise' : O(1)}
void power2(int F[2][2], int n)
{
    if( n == 0 || n == 1)
        return;
    int M[2][2] = {{1,1},{1,0}};

    power2(F, n/2);
    mul(F, F);

    if( n%2 != 0 )
        mul(F, M);
}


int fib1(int n)
{
    fib(n, power1)
}

int fib2(int n)
{
  fib(n, power2);
}

