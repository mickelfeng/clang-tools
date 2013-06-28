#include <stdio.h>
#include <stdlib.h>

//约瑟夫斯

int josephus(int n, int start ,int m) ;

int main()
{
    printf(" josephus(2, 0,3)  is %d\n", josephus(5, 0, 3));

    return 0;
}

/*
n : int  ->环中实例总数
start : int ->初始报数点
m : int -> 报数限制

理论:
1.n个实例报数如果从第一个开始报数 报数一次后 被去掉的下标 为 m % n, 剩下 n-1实例
2.n个实例报数如果从第第二个开始报数 报数一次后 被去掉的下标 为 (1+m) % n, 剩下 n-1实例
....
3.n个实例报数如果从第第start个开始报数 报数一次后 被去掉的下标 为 (start + m) % n, 剩下 n-1实例

归纳得到尾递归数学表达式
    f(n, start, m) = (start + m) n =1;
    f(n, start, m) = f(n -1, (start + m) % n, m)  n > 1

以下函数使用循环化处理(注明: 尾递归可以达到和循环一样的空间和效率)

*/

int josephus(int n, int start, int m)
{
    int i;
    int choice = start ;

    if(n < 1)
        return -1;


    for(i = n  ; i > 1; i--){

        choice = (choice + m) % i ;
        printf(" i = %d  is %d\n", i, choice);
    }


    return choice;
}
