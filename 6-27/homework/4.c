 ///
 /// @file    4.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*两个进程对同一个数据各加1千万，最终结果是2千万，结果打印后，父进程删除共享内存*/

#include "func.h"
#define N 10000000

int main(int argc, char **argv)
{
    int shmid = shmget(1000, 4096, 0666 | IPC_CREAT);
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

    int semid = semget(1000, 1, 0600 | IPC_CREAT);
    check_error(-1, semid, "semget");
    semctl(semid, 0, SETVAL, 1);
    struct sembuf sopp, sopv;
    sopp.sem_num = 0;
    sopp.sem_op = -1;
    sopp.sem_flg = SEM_UNDO;
    sopv.sem_num = 0;
    sopv.sem_op = 1;
    sopv.sem_flg = SEM_UNDO;
    if (!fork())
    {
        for(int i = 0; i < N; i++)
        {
            semop(semid, &sopp, 1);
            p[0] = p[0] + 1;
            semop(semid, &sopv, 1);
        }
    }
    else
    {
        for(int i = 0; i < N; i++)
        {
            semop(semid, &sopp, 1);
            p[0] = p[0] + 1;
            semop(semid, &sopv, 1);
        }
        wait(NULL);
        printf("%d\n", p[0]);
        int ret = semctl(semid, 0, IPC_RMID);
		check_error(-1, ret, "semctl");
    }
    return 0;
}
