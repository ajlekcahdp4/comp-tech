#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(){
int *ptr;
int md, flag;
key_t key;
int fd;
if((key = ftok("./2-tok", 0)) < 0){
    printf("Can\'t generate token\n");
    exit(-1);
}
if((md = shmget(key, 8192*sizeof(int), 0)) < 0){
    printf("Can\'t find shared memory\n");
    exit(-1);
}
if((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
    printf("Can't attach shared memory\n");
    exit(-1);
}

int i;
i = 0;
printf("2-write.c:\n");
printf("-----------------------------------------------------------\n\n");
while (ptr[i] != EOF ){
    putchar(ptr[i]);
    ++i;
}
if(shmctl(md, IPC_RMID, NULL) < 0){
    printf("Can't free shared memory\n");
    exit(-1);
}
printf("\nAll shared mamory released\n\n");
return 0;
}