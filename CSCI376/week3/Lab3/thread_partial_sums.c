#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS 3
#define ARRAY_SIZE 100000000

struct part{
    int *arr, beg, end;  // Input values
    int sum;             // Return value
};

// Finds the partial sum of a partition
void* sumPartition(void* params){
    struct part* data = (struct part*)params;

    data->sum = 0;
    for(int i = data->beg; i < data->end; i++){
        data-> sum += data->arr[i];
    }
}

int main(){
    struct part params[3];
    pthread_t handle[3];
    int* arr = (int*)malloc(ARRAY_SIZE * sizeof(int));

    // Initialize the array to 1 from start to finish
    for(int i = 0; i < ARRAY_SIZE; i++){
        arr[i] = 1;
    }
    
    // Create the partitions and start the threads
    for(int i = 0; i < THREADS; i++){
        params[i].arr = arr;
        params[i].beg = i*ARRAY_SIZE/THREADS;
        params[i].end = (i+1)*ARRAY_SIZE/THREADS;
        pthread_create(&handle[i], NULL, sumPartition, (void*)&params[i]);
    }

    int totalSum = 0;
    // Join the threads and add the partial sum to the total
    for(int i = 0; i < THREADS; i++){
        pthread_join(handle[i], NULL);
        totalSum += params[i].sum;
        printf("Partial Sum (%d) is: %d\n", i+1, params[i].sum);
    }

    printf("Total Sum is: %d\n", totalSum);
    return 0;
}