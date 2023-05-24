 ///
 /// @file    waitpid_nowait.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	pid_t pid;
	pid = fork();
	if (!pid)
	{
		printf("I am child,pid=%d\n", getpid());
		sleep(5);
		return 5;
	}
	else
	{
		printf("I am parent\n");
		int status;
		pid_t child_pid;
		sleep(1);
		child_pid = waitpid(pid, &status, WNOHANG); // 等待子进程退出
		printf("child_pid is %d\n", child_pid);
		if (WIFEXITED(status))
		{
			printf("exit status value=%d\n", WEXITSTATUS(status));
		}
		else
		{
			printf("child process core dump\n");
		}
		return 0;
	}
}

