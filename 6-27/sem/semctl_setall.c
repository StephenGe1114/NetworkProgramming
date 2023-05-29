 ///
 /// @file    semctl_setall.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	int sem_id;
	sem_id = semget(1000, 2, IPC_CREAT | 0600);
	check_error(-1, sem_id, "semget");
	unsigned short arr[2] = {1, 5};
	int ret = semctl(sem_id, 0, SETALL, arr);
	check_error(-1, ret, "semctl");
	memset(arr, 0, sizeof(arr));
	ret = semctl(sem_id, 0, GETALL, arr);
	printf("arr[0]=%d,arr[1]=%d\n", arr[0], arr[1]);
	return 0;
}

