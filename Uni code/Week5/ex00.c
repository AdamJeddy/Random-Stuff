#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>

#define ARRAY_SIZE 100000000
#define THREAD_COUNT 2
#define FORK_COUNT 4
#define ADD 4
#define SUBTRACT 9

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER();

struct Shared
{
    int *arr, beg, end, val; // Inputs
};

void *AdderMethod(void *lparams)
{
    struct Shared temp = *(struct * Shared) lparams;

    for (int i = temp.beg; i < temp.end; i++)
    {
        // Prob. add a lock
        temp.arr[i] += ADD;
        // Unlock it
    }
}

int main()
{
    // Open a file and semaphore
    FILE *file = fopen("result.txt", "w");
    sem_t *sem = sem_open("/sem", O_CREAT, 0666, 1);

    // Declare and Initialize the array from 0 to Array size
    int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = i;

    // Declare children
    pid_t forks[FORK_COUNT];
    memset(forks, 0, FORK_COUNT * sizeof(pid_t));

    for (int i = 0; i < FORK_COUNT; i++)
    {
        struct Shared sharedParams[THREAD_COUNT];

        for (int i = 0; i < THREAD_COUNT; i++)
        {
            sharedParams[j].arr = arr;
            sharedParams[j].beg = j * ARRAY_SIZE / THREADS;
            sharedParams[j].end = (j + 1) * ARRAY_SIZE / THREADS;
        }
        sharedParams[0].val = 4;
        sharedParams[1].val = -9;

        pthread_create(&handle[0], NULL, AdderMethod, (void *)&sharedParams[0]);
        pthread_create(&handle[1], NULL, AdderMethod, (void *)&sharedParams[1]);

        pthread_join(handle[0], NULL);
        pthread_join(handle[1], NULL);
    }

    for (int i = 0; i < FORK_COUNT; i++)
    {
        /* code */
    }
    

    free(arr);
}