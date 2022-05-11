#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define ARRAY_SIZE 50000

pthread_mutex_t myMutex;
double average_var = 0;

struct task3
{
    int *arr, start, end;
    // double average = 0;
};

void *average(void *lparam)
{
    struct task3 temp = *(struct task3*) lparam;
    int sum = 0;

    for (int i = temp.start; i < temp.end; i++)
        sum += temp.arr[i];

    pthread_mutex_lock(&myMutex); // Lock
    average_var += sum;
    pthread_mutex_unlock(&myMutex); // Unlock
}

void *standardDeviation(void *lparam)
{
}

int main(int argc, char **argv)
{
    // 2 threads are created if thread count isnt specified
    int thread_count = 2;
    if (argc > 1)
        thread_count = atoi(argv[1]);
    pthread_t handle[thread_count];
    printf("%d number of threads will be used\n", thread_count);

    // (1) Create an array of 50,000 ints
    int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));

    // (2) Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = i + 1;
    }

    // (3) Find the average of the integers by summing up the elements using multiple threads
    struct task3 params[thread_count];
    pthread_mutex_init(&myMutex, NULL);

    for (int i = 0; i < thread_count; i++)
    {
        params[i].arr = arr;
        params[i].start = i * ARRAY_SIZE / thread_count;
        params[i].end = (i + 1) * ARRAY_SIZE / thread_count;
        pthread_create(&handle[i], NULL, average, (void *)&params[i]);
    }
    // Join the threads
    for (int i = 0; i < thread_count; i++)
        pthread_join(handle[i], NULL);
    average_var /= ARRAY_SIZE;

    printf("Array average: %f\n", average_var);

    pthread_mutex_destroy(&myMutex);
    free(arr);
}