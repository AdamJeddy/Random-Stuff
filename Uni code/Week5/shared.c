#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define TEST_COUNT 10
#define ARRAY_SIZE 100000000
#define THREADS 4

struct Shared{
    int *arr, beg, end;	// Inputs
};

int sharedSum;
void* sumArrayShared(void* lparams){
    struct Shared data = *(struct Shared*)lparams;
	
    for(int i=data.beg; i<data.end; i++) {
        sharedSum += data.arr[i];
    }
}

long int getTimeDiff(const struct timeval beg, const struct timeval end){
    return (end.tv_sec - beg.tv_sec) * 1000000 +  end.tv_usec - beg.tv_usec;
}

int main(){
    struct Shared sharedParams[THREADS];
    pthread_t handle[THREADS];
    
    struct timeval start, end;
    long micros;

    int* arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
    // Initialize the array to 1 from start to finish
    for(int i = 0; i < ARRAY_SIZE; i++){
        arr[i] = 1;
    }

    gettimeofday(&start, NULL);	// Start Timer  
    
    // Run X number of tests to take an average time
    for(int i=0; i<TEST_COUNT; i++){
        // Initialize the result to 0
        sharedSum = 0;
    	
        // Partition and Start Threads
        for(int j = 0; j < THREADS; j++){
            sharedParams[j].arr  = arr;
            sharedParams[j].beg  = j*ARRAY_SIZE/THREADS;
            sharedParams[j].end  = (j+1)*ARRAY_SIZE/THREADS;
            pthread_create(&handle[j], NULL, sumArrayShared, (void*)&sharedParams[j]);
        }
		
        // Wait for the Threads to finish
        for(int j = 0; j < THREADS; j++){
            pthread_join(handle[j], NULL);
        }
    }
    
    gettimeofday(&end, NULL);	// End Timer  
    micros = getTimeDiff(start, end);
    printf("Shared Method Time Taken: %ldus\n", micros/TEST_COUNT );
    printf("Sum of the array is: %d\n", sharedSum);
    
    free(arr);
}