 ///
 /// @file    6.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*通过fork创建子进程，然后父进程通过wait回收，同时拿到子进程的返回值*/

#include "func.h"

int main()
{
    if (!fork())
    {
        return 5;
    }
    else
    {
        int status;
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("%d\n", WEXITSTATUS(status));
        } else {
            printf("error\n");
        }
    }
    return 0;
}
