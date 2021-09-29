#include <bits/stdc++.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

using namespace std;

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

int main(int argc, char **argv)
{
    int r, k, n, status;
    r = atoi(argv[1]);
    k = atoi(argv[2]);
    n = atoi(argv[3]);
    int pid[n];

    for (int i = 0; i < n; i++)
    {
        if((pid[i] = fork()) < 0 ){
            printf("Failed to fork process %d", i);
            exit(1);
        }
        if (pid[i] == 0)
        {
            //Faz conexão pelo socket
            //request da permissão
            //escrever no arquivo
            //Enviar o release
        }
    }

    while (n > 0)
    {
        wait(&status);
        n--;
    }
}
