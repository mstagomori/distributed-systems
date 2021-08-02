#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



// Defines the server port 
#define PORT 4242


// Sockets buffers length 
#define LEN 4096


// Server address 
#define SERVER_ADDR "127.0.0.1"

int random_number(int number) {

    // Get the system time.
    unsigned seed = time(0);
    
    // Seed the random number generator.
    srand(seed);

    int a = rand();

    // Takes the random number to 1-100 range
    int b = a%100 + 1;

    return (b + number);
}

//Main execution of the client program of our simple protocol
int main(int argc, char *argv[]) {

    // Server socket 
    struct sockaddr_in server;
    // Client file descriptor for the local socket 
    int sockfd;

    int len = sizeof(server);
    int slen;

    // Receive buffer 
    char buffer_in[LEN];
    // Send buffer 
    char buffer_out[LEN];

    fprintf(stdout, "Starting Client ...\n");

    //Creates a socket for the client
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error on client socket creation:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Client socket created with fd: %d\n", sockfd);

    // Defines the connection properties 
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    memset(server.sin_zero, 0x0, 8);


    // Tries to connect to the server 
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Can't connect to server");
        return EXIT_FAILURE;
    }

    // Receives the presentation message from the server 
    if ((slen = recv(sockfd, buffer_in, LEN, 0)) > 0) {
        buffer_in[slen + 1] = '\0';
        fprintf(stdout, "Server says: %s\n", buffer_in);
    }

    char *p;
    int number_of_randoms;

    long conv = strtol(argv[1], &p, 10);

    number_of_randoms = conv;

    int number = 0;
    char message[20];

    //Commuicate with the server until the exit message come
    for (int i = 0; i<number_of_randoms; i++) {

        // Zeroing the buffers 
        memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);

        number = random_number(number);
        snprintf(message, 10, "%d", number);

        // fprintf(stdout, "Say something to the server: ");
        // fgets(buffer_out, LEN, stdin);

        // Sends the read message to the server through the socket 
        send(sockfd, message, strlen(message), 0);

        // Receives an answer from the server 
        slen = recv(sockfd, buffer_in, LEN, 0);
        printf("Server answer: %s\n", buffer_in);
    }

    // Zeroing the buffers 
    memset(buffer_in, 0x0, LEN);
    memset(buffer_out, 0x0, LEN);

    char final_message[20] = "bye";

    // Sends the read message to the server through the socket 
    send(sockfd, final_message, strlen(final_message), 0);

    // Receives an answer from the server 
    slen = recv(sockfd, buffer_in, LEN, 0);
    printf("Server answer: %s\n", buffer_in);

    // Close the connection whith the server 
    close(sockfd);

    fprintf(stdout, "\nConnection closed\n\n");

    return EXIT_SUCCESS;
}