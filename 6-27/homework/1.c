 ///
 /// @file    1.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*创建一个无名管道，fork子进程，然后子进程向管道写端写Hello，父进程接收数据并打印*/

#include "func.h"

int main()
{
    int fds[2];
    int ret = pipe(fds);
    if (-1 == ret)
    {
        perror("pipe");
        return -1;
    }

    if (!fork())
    {
        close(fds[0]);
        write(fds[1], "hello", 5);
        close(fds[1]);
    }
    else
    {
        close(fds[1]);
        wait(NULL);
        char buf[128] = {0};
        read(fds[0], buf, sizeof(buf));
        printf("buf = %s\n", buf);
        close(fds[0]);
    }
    return 0;
}
