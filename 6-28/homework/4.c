 ///
 /// @file    4.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*sigaction实现2号信号，屏蔽3号信号的执行效果，同时在2号信号的信号处理流程中，判断3号信号是否被挂起*/

#include "func.h"

void sigfunc(int signum, siginfo_t* siginfo, void* p)
{
    printf("before sleep signum = %d\n", signum);
    sleep(3);
    sigset_t set;
    sigpending(&set);
    if(sigismember(&set, SIGQUIT))
    {
        printf("SIGQUIT is pending\n");
    } else {
        printf("SIGQUIT is not pending\n");
    }
    printf("after sleep signum = %d\n", signum);
}

int main(int argc, char **argv)
{
    struct sigaction act;
    bzero(&act, sizeof(act));
    act.sa_sigaction = sigfunc;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    sigaction(SIGINT, &act, NULL);
    while(1);

    return 0;
}
