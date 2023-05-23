 ///
 /// @file    chat_a.c
 /// @author  gsw(1499186594@qq.com)
 ///
   

/* 通过mkfifo命令新建两个管道文件1.pipe，2.pipe，然后两个进程通过管道文件实现即时聊天效果 */

#include "func.h"

int main(int argc, char **argv)
{
    args_check(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    if (-1 == fdr)
    {
        perror("open1");
        return -1;
    }
    int fdw = open(argv[2], O_WRONLY);
    if (-1 == fdr)
    {
        perror("open2");
        return -1;
    }
    printf("fdr = %d, fdw = %d\n", fdr, fdw);

    fd_set set;
    char buf[128] = {0};
    int ret;
    while (1)
    {
        FD_ZERO(&set);
        FD_SET(0, &set);
        FD_SET(fdr, &set);
        ret = select(fdr + 1, &set, NULL, NULL, NULL);
        if (ret > 0)
        {
            if (FD_ISSET(fdr, &set))
            {
                memset(buf, 0, sizeof(buf));
                ret = read(fdr, buf, sizeof(buf));
                if (0 == ret)
                {
                    printf("byebye\n");
                    break;
                }
                else if (-1 == ret)
                {
                    perror("read");
                    return -1;
                }
                else if (ret > 0)
                {
                    printf("%s\n", buf);
                }
            }
            if (FD_ISSET(0, &set))
            {
                memset(buf, 0, sizeof(buf));
                ret = read(0, buf, sizeof(buf));
                if (0 == ret)
                {
                    printf("byebye\n");
                    break;
                }
                else if (-1 == ret)
                {
                    perror("read");
                    return -1;
                }
                else if (0 < ret)
                {
                    ret = write(fdw, buf, strlen(buf) - 1);
                    if (-1 == ret)
                    {
                        perror("write");
                        return -1;
                    }
                }
            }
        }
        if (ret < 0)
        {
            perror("select");
            return -1;
        }
    }

    close(fdr);
    close(fdw);

    return 0;
}
