#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LAST_MESSAGE 255

int main(void)
{
    
   int msqid;
   char pathname[]="09-4-client.c";
   key_t  key;
   int i,len;
   struct mymsgbuf
   {
      long mtype;
      struct { 
        short sinfo;
        float finfo;
      } info;
   } mybuf;
   /* Create or attach message queue  */
   
   key = ftok(pathname, 0);
   
   if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t get msqid\n");
      exit(-1);
   }

   /* Send information */
   len = sizeof(struct mymsgbuf);
   pid_t chpid = fork();

   switch (chpid)
   {
   case 0: /* child */
	{
      while (1)
      {
         sleep(1);
         printf ("child loop iteration\n");
         for (i = 1; i <= 5; i++){
            mybuf.mtype = 1;
            mybuf.info.finfo = 1.0;
            mybuf.info.sinfo = 1;
            
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
            }
         }   
      }
   }
   case -1: /* error */
   {
        fprintf(stderr, "Error occured!\n");
        exit(0);
   }
   default: /*parent*/
   {
      while (1)
      {
         printf ("parent loop iteration\n");
         for (i = 1; i <= 5; i++){
            
            mybuf.mtype = 2;
            mybuf.info.finfo = 2.0;
            mybuf.info.sinfo = 2;
            len = sizeof(struct mymsgbuf);
            
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
            }
         }   
         sleep(1);
      }
   }
   };
   return 0;    
}
