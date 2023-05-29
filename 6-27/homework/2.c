 ///
 /// @file    2.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*新建共享内存，连接，然后往共享内存写入How are you,然后另外一个进程连接共享内存，读取数据并打印显示*/

#include "func.h"

int main(int argc, char **argv)
{
    args_check(2, argc);
    key_t key = ftok(argv[1], 1);
    if (-1 == key)
    {
        perror("ftok");
        return -1;
    }
    int shmid = shmget(key, 4096, 0666 | IPC_CREAT);
    if (-1 == shmid)
    {
        perror("shmget");
        return -1;
    }
    char *p = (char *)shmat(shmid, NULL, 0);
    if ((char *)-1 == p)
    {
        perror("shmat");
        return -1;
    }
    if (!fork())
    {
        char buf[128] = "how are you";
        strcpy(p, buf);
    }
    else
    {
        wait(NULL);
        printf("%s\n", p);
    }
    return 0;
}
