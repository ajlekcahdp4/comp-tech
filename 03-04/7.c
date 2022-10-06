#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid, ppid, chpid;
    int a = 0;

    chpid = fork();
    switch (chpid)
    {
    case 0: /* child */
	    a+=666;
        break;
    case -1: /* error */
        fprintf(stderr, "Error occured!\n");
        exit(0);
    default: /*parent*/
    /* print manual of "find" cmd to the man.txt file */
        (void) execle("/bin/man", "/bin/man", "find", (char*)NULL);
    }

    return 0;

}
