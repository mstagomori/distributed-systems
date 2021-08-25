#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <atomic>
#include <numeric>
#include <thread>

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;

void acquire() {
    while(lock_stream.test_and_set());
}

void release() {
    lock_stream.clear();
}

std::vector<signed char> createVector(long long int N) {

    std::vector<signed char> numbersVector;

    for (int i = 0; i<N; i++) {
        // Get the system time.
        unsigned seed = time(0);
        
        // Seed the random number generator.
        srand(seed);

        // Generate a random number between -100 and 100
        int a = rand()%200 - 100;

        numbersVector.push_back(a);
    }
    return numbersVector;
}

void accumulator(std::vector<signed char>::const_iterator start, std::vector<signed char>::const_iterator end, long int *totalSum) {
    long int portionSum = std::accumulate(start, end, 0);

    // critical region: adding portionSum to totalSum
    acquire();
    *totalSum += portionSum;
    release();
}

int main(int argc, char *argv[]) {
    clock_t start, end;

    long long int N[3] = {100000000, 1000000000, 10000000000};
    int K[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

    int k_index, n_index = 0;

    long int totalSum = 0;

    for (int n_index = 0; n_index < 3; n_index++) {
        std::vector<signed char> numbersVector = createVector(N[n_index]);

        for (int k_index = 0; k_index < 9; k_index++) {
            int portion = N[n_index] / K[k_index];

            std::vector<std::thread> threads;

            start = clock();
            // create threads
            for (int i = 0; i<K[k_index]; i++) {
                std::thread th(accumulator, numbersVector.begin() + (i * portion), numbersVector.end() - ((K[k_index]-1-i) * portion), &totalSum);
                threads.push_back((std::thread&&) (th));
                std::cout << "working.. | K = " << K[k_index];
            }

            // waits for threads to finish
            for (int i = 0; i < K[k_index]; i++) {
                threads[i].join();
            }
            end = clock();

            // time in ms
            double time = ((end-start) / (double)(CLOCKS_PER_SEC/1000));
            std::cout << "N = " << N[n_index] << " | K = " << K[k_index] << " | Time = " << time << "\n";
        }

        std::cout << "\n";
    }

    return 0;
}