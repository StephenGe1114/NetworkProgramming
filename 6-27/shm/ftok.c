 ///
 /// @file    ftok.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main(int argc, char **argv)
{
	args_check(argc, 2);
	key_t key;
	key = ftok(argv[1], 1);
	printf("key=%d\n", key);
	return 0;
}

