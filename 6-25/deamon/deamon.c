 ///
 /// @file    deamon.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
#include "func.h"

int main()
{
	if (!fork())
	{
		setsid();
		chdir("/");
		umask(0);
		int i;
		for (i = 0; i < 3; i++)
		{
			close(i);
		}
		while (1)
		{
			sleep(3);
			syslog(LOG_INFO, "%s%d\n", "I am dashen", i);
			i++;
		}
	}
	else
	{
		return 0;
	}
}

