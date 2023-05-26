 ///
 /// @file    4.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*能够得到孤儿进程*/

#include "func.h"

int main()
{
    if (!fork())
    {
        while(1);
    }
    else
    {
    }
    return 0;
}
