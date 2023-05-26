 ///
 /// @file    gmtime.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	time_t t;
	time(&t);
	struct tm *p;
	p = gmtime(&t);
	printf("%04d-%02d-%02d %02d:%02d:%02d %d %d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec, p->tm_wday, p->tm_yday);
	return 0;
}

