#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>

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
    if (p>0){
        cout<<"Parent"<< " "<< p<<"\n";
    }
    //Child Process
    else{
        cout<<"Child"<< " "<< p;
    }
    int incrementalNumber = 1;
    //for (int i = 0; i < 100; i++)
    //{
        //incrementalNumber = incrementByDelta(incrementalNumber);
        //if (isPrimeNumber(incrementalNumber))
        //{
            //cout << incrementalNumber << "\n";
        //}
    //}
    return 0;
}
