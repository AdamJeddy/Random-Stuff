#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define TEST_COUNT 10
#define ARRAY_SIZE 100000000

long int getTimeDiff(const struct timeval beg, const struct timeval end){
    return (end.tv_sec - beg.tv_sec) * 1000000 +  end.tv_usec - beg.tv_usec;
}

int main(){
    int totalSum;
    
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
        totalSum = 0;
    	
        // Sum the elements of the array
        for(int i=0; i<ARRAY_SIZE; i++){
            totalSum += arr[i];
        }
    }
    gettimeofday(&end, NULL);
    micros = getTimeDiff(start, end);
    printf("Basic Method Time Taken: %ldus\n", micros/TEST_COUNT );
    printf("Sum of the array is: %d\n", totalSum);
    
    free(arr);
}