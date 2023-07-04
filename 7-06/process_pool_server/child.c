#include "func.h"

int make_child(pData_t p, int process_num)
{
	int i;
	int fds[2];
	pid_t pid;
	for (i = 0; i < process_num; i++)
	{
		socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
		pid = fork();
		if (0 == pid)
		{
			close(fds[1]);
			child_handle(fds[0]); // 子进程必须在child_handle进行exit，否则子进程会继续for循环，创建的子进程不可控
		}
		close(fds[0]);
		p[i].pid = pid;	   // 子进程的pid保存下来
		p[i].fds = fds[1]; // 子进程的管道对端
		p[i].busy_flag = 0;
	}
	return 0;
}

void child_handle(int fds)
{
	int new_fd;
	int exit_flag = 0;
	char notbusy_flag = 1;
	while (1)
	{
		recv_fd(fds, &new_fd, &exit_flag); // 等待接收任务以及是否退出进程
		if (-1 == exit_flag) 
		{
			exit(0);
		}
		tran_file(new_fd);
		write(fds, &notbusy_flag, 1); // 通知父进程我不忙了
	}
}
