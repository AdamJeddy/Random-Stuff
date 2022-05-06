#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100
#define THREADS 3
#define PARTITION_SIZE (SIZE/THREADS)

struct arr{
    int *arr, beg, end, size;  // Input values
};

void* reverseArr(void* params)
{
    struct arr* data = (struct arr*)params;

    for (int i = data->beg; i < data->size; i++)
    {
        /* code */
    }
    

}

int main()
{
    int arr[SIZE];
    pthread_t handle[THREADS];
    int start, end;

    // Initialize the array to 100
    for (int i = 0; i < SIZE; i++)
        arr[i] = i + 1;
    
    // Create the partitions and start the threads
    for (int i = 0; i < THREADS; i++)
    {
        start = i * PARTITION_SIZE/2;
        end = (i + 1) * PARTITION_SIZE/2;
        pthread_create(&handle[i], NULL, reverseArr, (void *)&arr);
    }
    

    // Displaying the array
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    
    return 0;
}