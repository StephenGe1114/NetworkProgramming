 ///
 /// @file    sigaction_restart.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void sigfunc(int signum, siginfo_t *p, void *p1)
{
	printf("%d is coming\n", signum);
}

int main()
{
	struct sigaction act;
	bzero(&act, sizeof(act));
	act.sa_sigaction = sigfunc;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	int ret;
	ret = sigaction(SIGINT, &act, NULL);
	check_error(-1, ret, "sigaction");
	char buf[128] = {0};
	ret = read(0, buf, sizeof(buf));
	printf("ret=%d\n", ret);
}

