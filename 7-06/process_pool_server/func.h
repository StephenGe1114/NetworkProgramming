#include <sys/uio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <syslog.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>
#define args_check(a, b)            \
	{                               \
		if (a != b)                 \
		{                           \
			printf("error args\n"); \
			return -1;              \
		}                           \
	}
#define check_error(ret_val, ret, func_name) \
	{                                        \
		if (ret_val == ret)                  \
		{                                    \
			perror(func_name);               \
			return -1;                       \
		}                                    \
	}
#define check_thread_error(ret, func_name)               \
	{                                                    \
		if (0 != ret)                                    \
		{                                                \
			printf("%s is failed %d\n", func_name, ret); \
			return -1;                                   \
		}                                                \
	}
typedef struct // 用于父进程管理子进程
{
	pid_t pid;		 // 子进程的id
	int fds;		 // 子进程的管道对端，用于父子进程之间的通信，父进程向子进程分配任务，子进程通知自己非忙碌
	short busy_flag; // 忙碌标志，0代表非忙碌，1代码忙碌
} Data_t, *pData_t;

int make_child(pData_t, int);
void child_handle(int);
int recv_fd(int, int *, int *);
int send_fd(int, int, int);
int tran_file(int);
int send_n(int, char *, int);
#define FILENAME "file"
typedef struct // 文件传输过程中的协议
{
	int len;		// 控制数据,每个协议必带，这里记录buf的大小；
	char buf[1000]; // 判断buf的大小，不能用strlen，因为音频视频中本身就含有许多0；
} train;
