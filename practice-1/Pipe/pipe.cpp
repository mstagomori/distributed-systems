#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string.h>
#include <sstream>

using namespace std;

int randomNumberBetween1And100()
{
    srand(time(NULL));
    return rand() % 100 + 1;
}

int incrementByDelta(int number)
{
    return number + randomNumberBetween1And100();
}

bool isEvenlyDivisible(int numerator, int denominator)
{
    return (numerator % denominator) == 0;
}

bool isPrimeNumber(int number)
{
    for (int i = 2; i <= sqrt(number); i++)
    {
        if (isEvenlyDivisible(number, i))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int fd[2];

    int QTD_DE_NUM = stoi(argv[1]);

    char input_str[100];

    pid_t p;

    if(pipe(fd)==-1){
        cout<<"Pipe Failed";
        return 1;
    }

    p=fork();

    if(p<0){
        cout<<"Fork Failed";
        return 1;
    }

    //Parent Process
    // Produtor
    if (p>0){
        close(fd[0]);
        char num[20];
        int incrementalNumber = 1;
        for (int i =0; i< QTD_DE_NUM; i++){
            sprintf(num, "%d", incrementalNumber);
            write(fd[1], num, 50);
            incrementalNumber = incrementByDelta(incrementalNumber);
        }
        sprintf(num, "%d", 0);
        write(fd[1], num, 20);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    //Child Process
    else{
        char readNumber[20];
        int intReadNumber = 0;
        close(fd[1]);
        for (int i = 0; i < QTD_DE_NUM + 1; i++)
        {
            read(fd[0], readNumber, 50);
            intReadNumber = stoi(readNumber);
            if (isPrimeNumber(intReadNumber) && intReadNumber != 0)
                cout << readNumber << "\n";
            if(intReadNumber == 0) break;
        }
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    return 0;
}
