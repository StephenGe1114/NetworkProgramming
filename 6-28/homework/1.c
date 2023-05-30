 ///
 /// @file    1.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*IPC_PRIVATE方式新建消息队列，fork子进程，父进程发送消息，子进程读取并打印，父进程回收子进程后，删除消息队列*/

#include "func.h"

struct msgbuf
{
    long mtype;
    char buf[128];
};

int main(int argc, char **argv)
{
    int msgid = msgget(0, 0600 | IPC_CREAT);
    check_error(-1, msgid, "msgget");

    struct msgbuf msg;
    bzero(&msg, sizeof(struct msgbuf));
    int ret;

    if (!fork())
    {
        bzero(&msg, sizeof(struct msgbuf));
        msg.mtype = 2;
        ret = msgrcv(msgid, &msg, sizeof(msg.buf), msg.mtype, 0);
        printf("buf = %s\n", msg.buf);
    }
    else
    {
        msg.mtype = 2;
        strcpy(msg.buf, "hello");
        ret = msgsnd(msgid, &msg, strlen(msg.buf), 0);
        check_error(-1, ret, "msgsnd");
        wait(NULL);
		sleep(5);
        ret = msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
