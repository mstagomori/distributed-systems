#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>

int check_process(pid_t pid) {

    // Checa se o processo existe enviando um kill com signal 0
    if (0 == kill(pid, 0)) {
        printf("Process exists\n");
        return(1);
    } 
    else {
        printf("ERROR: Process does NOT exist\n");
        return(0);
    }
}

int main(int argc, char *argv[]){

    char *p;
    int pid;

    long conv = strtol(argv[1], &p, 10);

    pid = conv;

    // Se o processo existe
    if (check_process(pid)) {

        if (strcmp ("SIGUSR1", argv[2]) == 0) {
            kill(pid, SIGUSR1);
        }

        if (strcmp ("SIGUSR2", argv[2]) == 0) {
            printf("SIGUSR2 SENT");
            kill(pid, SIGUSR2);
        }

        if (strcmp ("SIGTERM", argv[2]) == 0) {
            printf("SIGTERM SENT");
            kill(pid, SIGTERM);
        }
        
    }

    return 0;
}