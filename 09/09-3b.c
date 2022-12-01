#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void)
{
    int msqid;
    char pathname[]="09-1a-modified.c";
    key_t  key;
    int msglen, maxlen;

    struct mymsgbuf
   {
      long mtype;
      struct { 
        short sinfo;
        float finfo;
      } info;
   } mybuf;
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }
    
    for (int i = 1; i <= 5; ++i) {
       
       maxlen = sizeof(struct mymsgbuf);;
       
       if (msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0) < 0){
         printf("Can\'t receive message from queue\n");
         exit(-1);
       }
       
       printf("message type = %ld, sinfo = %d, finfo = %f\n", mybuf.mtype, mybuf.info.sinfo, mybuf.info.finfo);
    }    


    for (int i = 1; i <= 5; i++){
      
      mybuf.mtype = 2;
      mybuf.info.finfo = 2.0;
      mybuf.info.sinfo = 2;
      msglen = sizeof(struct mymsgbuf);
      
      if (msgsnd(msqid, (struct msgbuf *) &mybuf, msglen, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
      }
   }    

    return 0;       
}
