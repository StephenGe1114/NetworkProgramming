 ///
 /// @file    msgctl.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	int msg_id = msgget(1000, IPC_CREAT | 0600);
	check_error(-1, msg_id, "msgget");
	int ret = msgctl(msg_id, IPC_RMID, NULL);
	check_error(-1, ret, "msgctl");
	return 0;
}

