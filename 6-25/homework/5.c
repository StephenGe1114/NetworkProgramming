 ///
 /// @file    5.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*通过fork创建进程，能够产生僵尸进程*/

#include "func.h"

int main()
{
    if (!fork())
    {

    }
    else
    {
        while(1);
    }
    return 0;
}
