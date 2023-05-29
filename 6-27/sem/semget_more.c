 ///
 /// @file    semget_more.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	int sem_id;
	sem_id = semget(1001, 2, IPC_CREAT | 0600);
	check_error(-1, sem_id, "semget");
	return 0;
}

