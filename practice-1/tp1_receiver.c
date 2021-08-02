#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>

// Signal handler functions
void usr1_handler(int num) {
    write(STDOUT_FILENO, "Signal USR1 Received\n", 22);
}
void usr2_handler(int num) {
    write(STDOUT_FILENO, "Signal USR2 Received\n", 22);
}
void int_handler(int num) {
    write(STDOUT_FILENO, "Signal TERM Received\n", 22);
    kill(getpid(), SIGTERM);
}

int main(int argc, char *argv[]) {

    // Declaring signals to be waiting for and respective handler functions
    signal(SIGUSR1, usr1_handler);
    signal(SIGUSR2, usr2_handler);
    signal(SIGINT, int_handler);

    // Transforming int pid to string pid (spid)
    int pid = getpid();
    char spid[10];
    snprintf(spid, 10, "%d", pid);

    // Transforming argv[1] to int 0 or 1 and saving it on wait variable
    char *wait_str;
    int wait;
    long conv = strtol(argv[1], &wait_str, 10);
    wait = conv;

    // Busy Wait prints the PID
    while(wait == 0) {
        write(STDOUT_FILENO, "BUSY WAIT PID = ", 17);
        write(STDOUT_FILENO, spid, 4);
        write(STDOUT_FILENO, "\n", 1);
        sleep(5);
    }

    // Blocking Wait prints the PID
    while(wait == 1) {
        write(STDOUT_FILENO, "BLOCKING WAIT PID = ", 21);
        write(STDOUT_FILENO, spid, 4);
        write(STDOUT_FILENO, "\n", 1);
        pause();
    }

    return 0;
}