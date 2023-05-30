 ///
 /// @file    msgsnd.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

struct msgbuf
{
	long mtype;
	char buf[64];
};

int main(int argc, char **argv)
{
	args_check(argc, 3);
	int msg_id = msgget(1000, IPC_CREAT | 0600);
	check_error(-1, msg_id, "msgget");
	struct msgbuf msg;
	msg.mtype = atoi(argv[1]); // 一定要是正整数
	strcpy(msg.buf, argv[2]);
	int ret = msgsnd(msg_id, &msg, strlen(msg.buf), 0);
	check_error(-1, ret, "msgsnd");
	return 0;
}

