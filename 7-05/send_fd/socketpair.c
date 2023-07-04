 ///
 /// @file    socketpair.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
    int fds[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
    char buf[128] = {0};
    if (!fork())
    {
        close(fds[1]);
        read(fds[0], buf, sizeof(buf));
        printf("I am child, fds[0] =%d, buf = %s\n", fds[0], buf);
        write(fds[0], "hello", 5);
        return 0;
    }
    else
    {
        close(fds[0]);
        write(fds[1], "world", 5);
        read(fds[1], buf, sizeof(buf));
        printf("I am parent, fds[1] = %d, buf = %s\n", fds[1], buf);
        wait(NULL);
    }
}

