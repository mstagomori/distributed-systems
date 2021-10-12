#include <bits/stdc++.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

#define PORT     8080
#define MAXLINE 1024

// retirado de: https://www.geeksforgeeks.org/write-your-own-atoi/
int atoi(const char *str)
{
    int sign = 1, base = 0, i = 0;

    // if whitespaces then ignore.
    while (str[i] == ' ')
    {
        i++;
    }

    // sign of number
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }

    // checking for valid input
    while (str[i] >= '0' && str[i] <= '9')
    {
        // handling overflow test case
        if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7))
        {
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}

// Request function, sends request to coordinator
char * request(char id) {
    int sockfd;
    char buffer[MAXLINE];
    char message[11] = "0|0|000000";

    // Identificador de mensagem Request = 1
    message[0] = "1";
    message[2] = id;
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n, len;
      
    sendto(sockfd, (const char *)message, strlen(message),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Request message sent.\n");
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    // Identificador de mensagem GRANT = 2
    if (buffer[0] == "2") {
        std::cout << "Request Granted, PID = " << id << "\n";
        return;
    } else {
        std::cout << "ERROR: RECEIVED NON GRANT MESSAGE";
    }
  
    close(sockfd);
}

void release(char id) {
    int sockfd;
    char buffer[MAXLINE];
    char *message[10] = "0|0|000000";

    // Identificador de mensagem Release = 3
    message[0] = "3";
    message[2] = id;
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n, len;
      
    sendto(sockfd, (const char *)message, strlen(message),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Release message sent.\n");
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
  
    close(sockfd);
}

int main(int argc, char **argv) {
    int r, k, n, status;
    r = atoi(argv[1]);
    k = atoi(argv[2]);
    n = atoi(argv[3]);
    int pid[n];

    clock_t time;

    for (int i = 0; i < n; i++)
    {
        if((pid[i] = fork()) < 0 ){
            printf("Failed to fork process %d", i);
            exit(1);
        }
        if (pid[i] == 0)
        {

            for (int j = 0; j < r; j++) {
                int id = getpid();
                char stringId[11];
                itoa(id, stringId, 10);
                //Faz conexão pelo socket
                // request da permissão
                request(stringId);
                //escrever no arquivo
                time = clock();
                result.open("resultados.txt", std::ofstream::out | std::ofstream::app);
                result << time + " " << id << std::endl;
                result.close();

                // espera k segundos antes de enviar o release
                sleep(k);

                //Enviar o release
                release(stringId);
            }
        }
    }

    while (n > 0)
    {
        wait(&status);
        n--;
    }
}
