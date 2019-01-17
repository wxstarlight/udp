#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/route.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GATEWAY     "192.168.1.1"
#define NET_MAST    "255.255.255.0"

void addGateway() { 
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
 
    struct rtentry route;
    memset(&route, 0, sizeof(route));
 
    struct sockaddr_in *addr = (struct sockaddr_in *)&route.rt_gateway;
    addr->sin_family = AF_INET;    
    if (inet_pton(AF_INET, GATEWAY, &(addr->sin_addr.s_addr)) <= 0) {
        fprintf(stderr, "inet_pton error! errno:%d, %s\n", errno, strerror(errno));
		exit(-1);
	}
 
    addr = (struct sockaddr_in*) &route.rt_genmask;
    addr->sin_family = AF_INET;
    if (inet_pton(AF_INET, NET_MAST, &(addr->sin_addr.s_addr)) <= 0) {
        fprintf(stderr, "inet_pton error! errno:%d, %s\n", errno, strerror(errno));
		exit(-1);
	}
 
    route.rt_flags = RTF_UP | RTF_GATEWAY;
    route.rt_metric = 0;
 
    if (ioctl(fd, SIOCADDRT, &route) < 0) {
        fprintf(stderr, "ioctl error! errno:%d, %s\n", errno, strerror(errno));
        close(fd);
        exit(-1);
    }
 
    close(fd);
}

int main() {
    addGateway();
}
