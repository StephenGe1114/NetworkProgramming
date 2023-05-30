 ///
 /// @file    kill.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 3);
	int sig = atoi(argv[1]);
	pid_t pid = atoi(argv[2]);
	int ret;
	ret = kill(pid, sig);
	check_error(-1, ret, "kill");
	return 0;
}

