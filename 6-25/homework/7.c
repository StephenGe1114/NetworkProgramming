 ///
 /// @file    7.c
 /// @author  gsw(1499186594@qq.com)
 ///

/*创建一个deamon进程，每隔5秒，向/tmp下的文件log里写一句I have sleep 5*/

#include "func.h"

int main()
{
    if (!fork())
    {
        setsid();
        chdir("/");
        umask(0);
        for(int i = 0; i < 3; i++) {
            close(i);
        }
        while(1) {
            syslog(LOG_INFO, "%s\n", "I have sleep 5");
            sleep(5);
        }

    }
    else
    {

    }
    return 0;
}
   
