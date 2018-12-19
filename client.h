#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
 
#define MYPORT 5678
char* SERVERIP = "127.0.0.1";
 
#define ERR_EXIT(m) \
    do \
{ \
    perror(m); \
    exit(EXIT_FAILURE); \
    } while(0)
 
void echo_cli(int sock)
{
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVERIP);
    
    int ret;
    char sendbuf[1024] = {hello};
    char recvbuf[1024] = {0};
        
    printf("向服务器发送：%s\n",sendbuf);
    sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        
    ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
    printf("从服务器接收：%s\n",recvbuf);
        
    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(recvbuf));
    
    close(sock);
    
    
}
 
