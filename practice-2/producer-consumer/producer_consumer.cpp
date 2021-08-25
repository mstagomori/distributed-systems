#include<iostream>
#include<stdlib.h>
#include<semaphore.h>
#include<thread>
#include<cmath>
#include<vector>
#include<mutex>
#include<condition_variable>

using namespace std::chrono;

//Função para gerar um numero aleatório
int getRandomNumber();
//Função para verificar se um número é primo
bool isPrimeNumber(int num);
//Função 
void insertRandomNumberIntoArray(int[]);

class Semaphore
{
public:
  Semaphore(int count_ = 0) : count(count_)
  {
  }

  void pickLock()
  {
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    cv.notify_one();
  }
  void wait()
  {
    std::unique_lock<std::mutex> lock(mtx);
    while (count == 0)
      cv.wait(lock);
    count--;
  }

private:
  std::mutex mtx;
  std::condition_variable cv;
  int count;
};

class Counter
{
public:
  Counter()
  {
    this->counter = 0;
  }

  int getCount()
  {
    mutex.lock();
    int val = this->counter;
    mutex.unlock();
    return val;
  }

  void increment()
  {
    mutex.lock();
    this->counter++;
    mutex.unlock();
  }

  void decrement()
  {
    mutex.lock();
    this->counter--;
    mutex.unlock();
  }

private:
  std::mutex mutex;
  int counter;
};

int main(){
    int combinacoes[][2] = {{1,1},{1,2},{1,4},{1,8},{1,16},{2,1},{4,1},{8,1},{16,1}}; 
    int valoresN[] = {1,2,4,16,32};
    for(int i =0; i< sizeof(combinacoes)/sizeof(combinacoes[0]); i++ ){
        std::cout<<"Para combinação {Np , Nc} = {"<< combinacoes[i][0]<<" , "<<combinacoes[i][1]<<"}"<<std::endl;
        for(int j =0; j<sizeof(valoresN)/sizeof(valoresN[0]); j++){
            auto start = high_resolution_clock::now();

            srand (time(NULL));

            int Nc = combinacoes[i][0];
            int Np = combinacoes[i][1];
            int M =(int)10e5;
            int N = valoresN[j];

            Counter producerCounter;
            Counter consumerCounter;

            std::vector<std::thread> producers;
            std::vector<std::thread> consumers;

            std::vector<int> memory;

            Semaphore mutex(1);
            Semaphore empty(N);
            Semaphore full(0);
            for (int i = 0; i < Np; i++)
            {
                producers.push_back(std::thread([&]()
                {
                    while (producerCounter.getCount() < M)
                    {
                        producerCounter.increment();
                        empty.wait();
                        mutex.wait();
                        memory.push_back(getRandomNumber());
                        mutex.pickLock();
                        full.pickLock();
                    }
                }));
            }

            for (int i = 0; i < Nc; i++)
            {
                consumers.push_back(std::thread([&]()
                {
                    while (consumerCounter.getCount() < M)
                    {
                        consumerCounter.increment();
                        full.wait();
                        mutex.wait();
                        int num = memory.back();
                        memory.pop_back();
                        mutex.pickLock();
                        empty.pickLock();
                        //std::cout << num << " is prime: "<<isPrimeNumber(num)<<std::endl;
                    }
                }));
            }

            for (int i = 0; i < Np; i++)
                producers[i].join();
            for (int i = 0; i < Nc; i++)
                consumers[i].join();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);
            std::cout<< " N = "<< valoresN[j] << " => " <<  duration.count() << " " ;
        }
        std::cout<<std::endl;
    }
    return 0;
}

void insertRandomNumberIntoArray(std::vector<int> memory){
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