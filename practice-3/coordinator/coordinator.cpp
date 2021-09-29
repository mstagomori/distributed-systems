#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("Failed to create the socket");
        exit(1);
    }
    bzero((char *)&serv; _addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
}