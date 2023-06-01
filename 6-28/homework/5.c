 ///
 /// @file    5.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*通过sigprocmask阻塞2号信号，睡眠5秒后，解除阻塞，2号信号得到执行；在睡眠后，解除阻塞之前,通过sigpending检测是否有信号挂起*/

#include "func.h"

int main(int argc, char **argv)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, NULL);
    sleep(5);
    sigset_t pendSet;
    sigpending(&pendSet);
    if (sigismember(&pendSet, 2))
    {
        printf("2 is pending\n");
    }
    else
    {
        printf("2 is not pending\n");
    }
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    while (1)
        ;

    return 0;
}
