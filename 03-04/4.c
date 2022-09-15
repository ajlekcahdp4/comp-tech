#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
    for (i = 1; i < argc; i++)
        printf ("ARG%d = %s\n", i, argv[i]);
    for (i = 0; envp[i] != NULL ;i++)
        printf ("%s\n", envp[i]);
    return 0;
}   
