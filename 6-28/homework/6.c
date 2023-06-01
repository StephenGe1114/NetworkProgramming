 ///
 /// @file    6.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*使用真实计时器，实用计时器，虚拟计时器，统计程序执行时间，在实用计时器及虚拟计时器设定计时后，先睡眠，
  再让程序处于while（1）*/

#include "func.h"

void sigfunc(int signum)
{
    time_t t;
    time(&t);
    printf("%s\n", ctime(&t));

}

void real()
{
    sigfunc(0);
	signal(SIGALRM, sigfunc);
    struct itimerval t;
    bzero(&t, sizeof(t));
    t.it_value.tv_sec = 5;
    t.it_interval.tv_sec = 2;
    setitimer(ITIMER_REAL, &t, NULL);
    sleep(5);
    while(1);
}

void virtual()
{
    sigfunc(0);
	signal(SIGVTALRM, sigfunc);
    struct itimerval t;
    bzero(&t, sizeof(t));
    t.it_value.tv_sec = 5;
    t.it_interval.tv_sec = 2;
    setitimer(ITIMER_VIRTUAL, &t, NULL);
    sleep(5);
    while(1);
}

void prof()
{
    sigfunc(0);
	signal(SIGPROF, sigfunc);
    struct itimerval t;
    bzero(&t, sizeof(t));
    t.it_value.tv_sec = 5;
    t.it_interval.tv_sec = 2;
    setitimer(ITIMER_PROF, &t, NULL);
    sleep(5);
    while(1);
}

int main(int argc, char **argv)
{
//    real();
//	virtual();
	prof();
    return 0;
}
