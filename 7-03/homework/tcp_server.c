 ///
 /// @file    tcp_server.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*聊天室*/

#include "func.h"
#define N 5

int main(int argc, char **argv)
{
    args_check(3, argc);

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    check_error(-1, sfd, "socket");

    struct sockaddr_in ser;
    bzero(&ser, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(atoi(argv[2]));
    ser.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = bind(sfd, (struct sockaddr *)&ser, sizeof(ser));
    check_error(-1, ret, "bind");

    ret = listen(sfd, 10);
    check_error(-1, ret, "listen");

    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
	int len = sizeof(cli);
    fd_set rdSet, tmpSet;
    FD_ZERO(&rdSet);
    FD_ZERO(&tmpSet);
    FD_SET(STDIN_FILENO, &tmpSet);
    FD_SET(sfd, &tmpSet);
    char buf[128] = {0};
    int new_fd[N];
    memset(new_fd, -1, sizeof(new_fd));

    while (1)
    {
        FD_ZERO(&rdSet);
        memcpy(&rdSet, &tmpSet, sizeof(fd_set));
        ret = select(sfd + 6, &rdSet, NULL, NULL, NULL);
        if (ret > 0)
        {
            if (FD_ISSET(sfd, &rdSet))
            {
                for (int i = 0; i < N; i++)
                {
                    if (-1 == new_fd[i])
                    {
                        new_fd[i] = accept(sfd, (struct sockaddr *)&cli, &len);
                        printf("ip = %s, port = %d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
                        FD_SET(new_fd[i], &tmpSet);
                        break;
                    }
                }
            }
            for (int i = 0; i < N; i++)
            {
                if (new_fd[i] != -1 && FD_ISSET(new_fd[i], &rdSet))
                {
                    memset(buf, 0, sizeof(buf));
                    ret = recv(new_fd[i], buf, sizeof(buf), 0);
                    if (ret > 0)
                    {
                        printf("%s\n", buf);
                    }
                    if (ret == 0)
                    {
                        printf("Byebye\n");
                        FD_CLR(new_fd[i], &tmpSet);
                        close(new_fd[i]);
                        new_fd[i] = -1;
                    }
                }
            }
            if (FD_ISSET(STDIN_FILENO, &rdSet))
            {
                memset(buf, 0, sizeof(buf));
                read(STDIN_FILENO, buf, sizeof(buf));
                for (int i = 0; i < N; i++)
                {
                    if (new_fd[i] != -1)
                    {
                        ret = send(new_fd[i], buf, strlen(buf) - 1, 0);
                    }
                }
            }
        }
    }

    return 0;
}
