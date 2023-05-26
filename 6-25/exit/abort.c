 ///
 /// @file    abort.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

void print()
{
	printf("I am print");
	abort();
}

int main()
{
	printf("I am main\n");
	print();
	printf("after print\n");
	return 0;
}

