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

 
void echo_cli(int sock)
{
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVERIP);
    
    int ret;
    char sendbuf[1024] = {'h','e','l','l','o'};
    char recvbuf[1024] = {0};
        
    printf("client send to server：%s\n",sendbuf);
    sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        
    ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
    printf("client receive from server：%s\n",recvbuf);
    
    close(sock);
    
}
 
