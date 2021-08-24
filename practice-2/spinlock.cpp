#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
 
#define K 4

void *function(void *param)
{
       int id = *((int *)(param));
       int i, loops = 10;
       for(i = 0; i < loops; i++)
       {
            printf("thread %d: loop %d\n", id, i);
       }
       pthread_exit(NULL);
}

int createVector(int N) {

    int vector[N] = {};

    for (int i = 0; i<N; i++) {
        // Get the system time.
        unsigned seed = time(0);
        
        // Seed the random number generator.
        srand(seed);

        // Generate a random number between -100 and 100
        int a = rand()%201 - 100;

        vector[i] = a;
    }
    return vector;
}

int main(void)
{
    // pthread_t threads[K];
    // int thread_args[K];
    // int i;
    // printf("pre-execution\n");
    // for (i = 0; i < K; i++)
    // {
    //         thread_args[i] = i;
    //         pthread_create(&threads[i], NULL, function, (void *) &thread_args[i]);
    // }
    // printf("mid-execution\n");

    // for (i = 0; i < K; i++)
    // {
    //         pthread_join(threads[i], NULL);
    // }
    // printf("post-execution\n");
    // return EXIT_SUCCESS;

    int vetor = createVector(100);
    cout << vetor;

    return 0;
}