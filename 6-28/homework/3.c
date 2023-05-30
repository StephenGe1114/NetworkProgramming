 ///
 /// @file    3.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*sigaction实现2号，3号信号不断重入的执行效果*/

#include "func.h"

void sigfunc(int signum, siginfo_t* siginfo, void* p)
{
    printf("before sleep signum = %d\n", signum);
    sleep(3);
    printf("after sleep signum = %d\n", signum);
}

int main(int argc, char **argv)
{
    struct sigaction act;
    bzero(&act, sizeof(act));
    act.sa_sigaction = sigfunc;
    act.sa_flags = SA_SIGINFO | SA_NODEFER;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    while(1);

    return 0;
}
