 ///
 /// @file    sigprocmask.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	int ret;
	ret = sigprocmask(SIG_BLOCK, &mask, NULL);
	check_error(-1, ret, "sigprocmask");
	sleep(10);
	printf("you can see me\n");
	ret = sigprocmask(SIG_UNBLOCK, &mask, NULL);
	check_error(-1, ret, "sigprocmask");
	return 0;
}

