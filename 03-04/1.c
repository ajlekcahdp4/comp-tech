#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid, ppid, chpid;
    pid  = getpid();
    ppid = getppid();

    printf("My pid = %d, my ppid = %d\n", (int)pid, (int)ppid);

    return 0;

}
