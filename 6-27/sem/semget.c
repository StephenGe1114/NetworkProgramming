 ///
 /// @file    semget.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	int sem_id;
	sem_id = semget(1000, 1, IPC_CREAT | 0600);
	check_error(-1, sem_id, "semget");
	return 0;
}

