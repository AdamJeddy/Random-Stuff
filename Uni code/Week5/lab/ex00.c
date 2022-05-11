/*
Code explanation:
The threads run into race conditions when attempting to modify the shared count variable
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000

// Global variable
int count;
int *arr;

// Thread method to add every element in the array to the count
void *addElements(void *lparams)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        count += arr[i];
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

    pthread_t thr1, thr2;
    pthread_create(&thr1, NULL, addElements, NULL);
    pthread_create(&thr2, NULL, addElements, NULL);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    printf("Content of count is: %d\n", count);
    free(arr);
}
