
/* A simple daytime TCP client */

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    int    sockfd, n;
    char   recvline[1000];
    struct sockaddr_in servaddr;
    
    if(argc != 2){
       printf("Usage: a.out <IP address>\n");
       exit(1);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13);
    
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
       printf("Invalid IP address\n");
       exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
       printf("Can\'t create socket, errno = %d\n", errno);
       exit(1);
    }

    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
       printf("Can\'t connect, errno = %d\n", errno);
       close(sockfd);
       exit(1);
    }

    n = read(sockfd,recvline, 999);

    if(n < 0){
       printf("Can\'t read, errno = %d\n", errno);
       exit(1);
    }

    recvline[n] = 0;
    printf("%s", recvline);

    close(sockfd);
    return 0;
}
