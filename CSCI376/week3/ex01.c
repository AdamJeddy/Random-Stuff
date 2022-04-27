#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int globvar = 6;
int main(void)
{
    int w = 88;
    pid_t pid;
    printf( "Before fork()\n" );
    if ((pid = fork()) == 0)
    { /* child */
        globvar++;
        w++;
    }
    else if (pid > 0) /* parent */
        sleep(2);
    printf( "pid = % d, globvar = % d, w = % d\n", getpid(), globvar, w);
    return 0;
} /* end main */