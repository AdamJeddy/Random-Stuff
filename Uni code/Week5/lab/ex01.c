/*
ex00 is modified to add mutex locking and make the output correct
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000

// Global variable
pthread_mutex_t myMutex;
int count;
int *arr;

// Thread method to add every element in the array to the count
void *addElements(void *lparams)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        pthread_mutex_lock(&myMutex); // Lock
        count += arr[i];
        pthread_mutex_unlock(&myMutex); // Unlock
    }
}

int main()
{
    // Initialize the array to 1 from start to finish
    arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = 1;
    }

    // Initializing a mutex is necessary before using it
    // Alternatively use PTHREAD_MUTEX_INITIALIZER at declaration
    pthread_mutex_init(&myMutex, NULL);

    pthread_t thr1, thr2;
    pthread_create(&thr1, NULL, addElements, NULL);
    pthread_create(&thr2, NULL, addElements, NULL);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    // Destroying the mutex will deallocate its resources
    pthread_mutex_destroy(&myMutex);

    printf("Content of count is: %d\n", count);
    free(arr);
}
