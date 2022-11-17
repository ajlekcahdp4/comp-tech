#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 
int main(){
    int *ptr;
    int md, fd, flag;
    key_t key;
    if((key = ftok("./2-tok", 0)) < 0){
        printf("Error of generate token\n");
        exit(-1);
    }
    if((md = shmget(key, 8192*sizeof(int), 0777|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            printf("Error of create shared memory\n");
            exit(-1);
        }
        else {
            if((md = shmget(key, 8192*sizeof(int), 0)) < 0){
                printf("Error of find shared memory\n");
                exit(-1);
            }
        }
    }

    if((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
        printf("Error attach shared memory\n");
        exit(-1);
    }

    int i;
    i = 0;
    fd = open ("./2-write.c", O_RDONLY);
   
    while ((flag = read (fd, &ptr[i], 1)) > 0)
        i++;
    ptr[i+1]=EOF;
    
    if (flag < 0){
        printf ("Can not read file\n");
        exit (1);
    }
    
    if(shmdt(ptr) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    
    printf("\nWriting of text this programm successfull\n\n");
    
    return 0;
}
