 ///
 /// @file    msgrcv.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

struct msgbuf
{
	long mtype;
	char buf[64];
};

int main()
{
	int msg_id = msgget(1000, IPC_CREAT | 0600);
	check_error(-1, msg_id, "msgget");
	struct msgbuf msg;
	memset(&msg, 0, sizeof(msg));
	msg.mtype = 0; // 一定要是正整数
	int ret = msgrcv(msg_id, &msg, sizeof(msg.buf), 1, 0);
	check_error(-1, ret, "msgrcv");
	printf("msg=%s\n", msg.buf);
	return 0;
}

