 ///
 /// @file    3.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*通过fork创建子进程观察执行情况，通过execl实现子进程执行另外一个可执行程序*/

#include "func.h"

int main()
{
    pid_t pid = fork();
    if (!pid)
    {
        printf("I am child\n");

        execl("./add", "./add", "3", "4", NULL);
        while (1);

        printf("I am child, you can't see me\n");
    }
    else
    {
        printf("I am parent\n");
        printf("I am parent, you can't see me\n");
        while (1);
            
    }
    return 0;
}
