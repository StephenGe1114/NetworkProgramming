 ///
 /// @file    2.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*signal设置信号处理行为，演示不同信号到来时，后来的信号会打断原有信号的信号处理函数效果，相同信号无法打断的效果*/

#include "func.h"

void sigfunc(int signum)
{
    printf("before sleep signum = %d\n", signum);
    sleep(3);
    printf("after sleep signum = %d\n", signum);
}

int main(int argc, char **argv)
{
    signal(SIGINT, sigfunc);
    signal(SIGQUIT, sigfunc);
    while(1);

    return 0;
}
