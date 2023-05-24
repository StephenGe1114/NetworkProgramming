 ///
 /// @file    2.c
 /// @author  gsw(1499186594@qq.com)
 ///

/*通过fork创建子进程，让父子进程都打印pid，都处于while(1),然后用ps进程查看，查看完毕，用kill命令杀掉*/
   
#include "func.h"

int main()
{
	pid_t pid = fork();
	if(!pid) {
		printf("I am child pid = %d, ppid = %d\n", getpid(), getppid());
		while(1);

	} else {
        printf("I am parent pid = %d, subpid = %d\n", getpid(), pid);
		while(1);
	}
	
	return 0;
}

