#include<iostream>
#include<stdlib.h>
#include<semaphore.h>
#include<thread>
#include<cmath>
#include<vector>
#include<mutex>
#include<condition_variable>

//Função para gerar um numero aleatório
int getRandomNumber();
//Função para verificar se um número é primo
bool isPrimeNumber(int num);
//Função 
void insertRandomNumberIntoArray(int[]);

class Semaphore
{
public:
  Semaphore(int count_ = 0)
      : count(count_)
  {
  }

  inline void notify()
  {
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    cv.notify_one();
  }
  inline void wait()
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

class MutexCounter
{
public:
  MutexCounter()
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

  void incrementCount()
  {
    mutex.lock();
    this->counter++;
    mutex.unlock();
  }

  void decrementCount()
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
    srand (time(NULL));

    int Np;
    int Nc;
    int M =(int)10e5;
    int M = 10;
    int N = 10;

    MutexCounter producerCounter;
    MutexCounter consumerCounter;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    std::vector<int> memory;

    Semaphore mutex(1);
    Semaphore empty(N);
    Semaphore full(0);
    for (int i = 0; i < 2; i++)
    {
        producers.push_back(std::thread([&]()
        {
            while (producerCounter.getCount() < M)
            {
                producerCounter.incrementCount();
                empty.wait();
                mutex.wait();
                memory.push_back(getRandomNumber());
                mutex.notify();
                full.notify();
            }
        }));
    }

    for (int i = 0; i < 2; i++)
    {
        consumers.push_back(std::thread([&]()
        {
            while (consumerCounter.getCount() < M)
            {
                consumerCounter.incrementCount();
                full.wait();
                mutex.wait();
                int singlePrime = memory.back();
                memory.pop_back();
                mutex.notify();
                empty.notify();
                std::cout << singlePrime << " is prime: "<<isPrimeNumber(singlePrime)<<std::endl;
            }
        }));
    }

    for (int i = 0; i < 2; i++)
        producers[i].join();
    for (int i = 0; i < 2; i++)
        consumers[i].join();
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