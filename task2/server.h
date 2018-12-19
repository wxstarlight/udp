#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
 
#define MYPORT 5678
 
 
#define ERR_EXIT(m) \
    do { \
    perror(m); \
    exit(EXIT_FAILURE); \
    } while (0)
 
void echo_ser(int sock)
{
    char recvbuf[1024] = {0};
    char reply[]="hi";
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int n;
    
    while(1){
        peerlen = sizeof(peeraddr);
        memset(recvbuf, 0, sizeof(recvbuf));
        n = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                     (struct sockaddr *)&peeraddr, &peerlen);

        if(n > 0)
        {
            printf("server receive:%s\n",recvbuf);
            sendto(sock, reply, sizeof(reply), 0,
                   (struct sockaddr *)&peeraddr, peerlen);
            printf("server reply:%s\n",reply);
        }
        else
         break;
    }
 
    close(sock);
}
 
