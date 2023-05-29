 ///
 /// @file    3.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*两个进程对一个共享内存各加1000万，查看最后结果*/

#include "func.h"
#define N 10000000

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
    int *p = (int *)shmat(shmid, NULL, 0);
    if ((int *)-1 == p)
    {
        perror("shmat");
        return -1;
    }
    p[0] = 0;
    if (!fork())
    {
        for (int i = 0; i < N; i++)
        {
            p[0] = p[0] + 1;
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            p[0] = p[0] + 1;
        }
        wait(NULL);
        printf("%d\n", p[0]);
    }
    return 0;
}
