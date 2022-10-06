#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, ppid, chpid;
    int a = 0;

    chpid = fork();
    if (chpid == 0)
	    a+=666;
    else
	    a+=228;

    pid  = getpid();
    ppid = getppid();

    printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);

    return 0;

}
