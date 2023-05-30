 ///
 /// @file    sleep.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void sigfunc(int signum)
{
	signal(SIGALRM, SIG_DFL);
}

int main()
{
	signal(SIGALRM, sigfunc);
	alarm(3);
	pause(); // 放弃cpu，去睡眠队列
	return 0;
}

