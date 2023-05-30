 ///
 /// @file    setitimer_prof.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void sigfunc(int signum)
{
	time_t t;
	t = time(NULL); // 当前秒数返回给你
	printf("%s\n", ctime(&t));
}
int main()
{
	sigfunc(0); // kill(SIGALRM,0);
	struct itimerval t;
	bzero(&t, sizeof(t));
	t.it_value.tv_sec = 5;
	t.it_interval.tv_sec = 2;
	signal(SIGPROF, sigfunc);
	int ret;
	ret = setitimer(ITIMER_PROF, &t, NULL);
	check_error(-1, ret, "setitimer");
	char buf[128] = {0};
//	sleep(5);
	read(0, buf, sizeof(buf));
	while (1)
		;
	return 0;
}

