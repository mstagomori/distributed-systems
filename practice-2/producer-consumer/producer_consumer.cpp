#include<iostream>
#include<stdlib.h>
#include<semaphore.h>
#include<thread>
#include<cmath>
#include<vector>

using namespace std;

//Função para gerar um numero aleatório
int getRandomNumber();
//Função para verificar se um número é primo
bool isPrimeNumber(int num);
//Função 
void insertRandomNumberIntoArray(int[]);

int main(){
    srand (time(NULL));

    int NUMBER_OF_CONSUMERS = 1;
    int NUMBER_OF_PRODUCERS = 1;

    vector<thread> threads;
    vector<int> memory;
    for (int i = 0; i< 2; i++)
        threads.push_back(thread(insertRandomNumberIntoArray,memory));


    for(int i =0; i<2; i++){
        cout<<memory[i]<<"\n";
        threads[i].join();
    }
    return 0;
}

void insertRandomNumberIntoArray(vector<int> memory){
    int randNumber = getRandomNumber();
    memory.push_back(randNumber);
}

int getRandomNumber (){
     return (rand() % (int)pow(10.0, 7.0) + 1);
}

bool isPrimeNumber(int num){
    for (int i = 2; i < sqrt(num); i++)
        if ((num % i) == 0)
             return false;
    return true;
}