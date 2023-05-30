 ///
 /// @file    sigaction_siginfo.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void sigfunc(int signum, siginfo_t *p, void *p1)
{
	printf("%d is coming\n", signum);
	printf("sending pid=%d,uid=%d\n", p->si_pid, p->si_uid);
}

int main()
{
	struct sigaction act;
	bzero(&act, sizeof(act));
	act.sa_sigaction = sigfunc;
	act.sa_flags = SA_SIGINFO;
	int ret;
	ret = sigaction(SIGINT, &act, NULL);
	check_error(-1, ret, "sigaction");
	while (1)
		;
}

