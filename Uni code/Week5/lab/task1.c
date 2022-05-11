#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 4
#define ARRAY_SIZE 8

struct Index
{
    double *arr;
    int beg, end;
};

pthread_mutex_t myMutex;
double balance = 0;

double fetchBalance()
{
    sleep(1);
    return balance;
}

void updateBalance(double value)
{
    sleep(1);
    balance = value;
}

void *deposit(void *lparam)
{
    // [1] Implement the function
    struct Index var = *(struct Index *)lparam;

    for (int i = var.beg; i < var.end; i++)
    {
        pthread_mutex_lock(&myMutex); // Lock
        updateBalance(fetchBalance() + var.arr[i]);
        pthread_mutex_unlock(&myMutex); // Unlock
    }
}

int main()
{
    pthread_t threads[THREADS];
    double deposits[ARRAY_SIZE] = {
        72.5, 13.75, 50.5, 82.25,
        20.5, 64.75, 10.5, 199.25};

    // [2] Partition and start threads
    pthread_mutex_init(&myMutex, NULL);

    // Threads

    struct Index params[THREADS];
    for (int i = 0; i < THREADS; i++)
    {
        params[i].arr = deposits;
        params[i].beg = i * ARRAY_SIZE / THREADS;
        params[i].end = (i + 1) * ARRAY_SIZE / THREADS;
        pthread_create(&threads[i], NULL, deposit, (void *)&params[i]);
    }

    // wait for threads to finish
    for (int j = 0; j < THREADS; j++)
        pthread_join(threads[j], NULL);

    pthread_mutex_destroy(&myMutex);
    printf("Balance: %f\n", balance);
}
