#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

struct arrStruct 
{
	int size, oddCount, evenCount,
	int* array;
};

void* countOdd(void* params)
{
    struct Pow* data = (struct Pow*)params;
	data->oddCount = 0;
	
	for(int i = 0; i < data->size; i++)
		if (arr[i] % 2 == 1)
			data->oddCount++;
	
	return count;
}

void* countEven(void* params)
{
    struct Pow* data = (struct Pow*)params;
	data->evenCount = 0;
	
	for(int i = 0; i < data->size; i++)
		if (arr[i] % 2 == 0)
			data->evenCount++;
	
	return count;
}

int main(){
    // Create Array (1)
	int size = 100000000;
    int* arrTemp = (int*)malloc(size * sizeof(int));
	
	struct arrStruct arr = {size, 0, 0, &arrTemp};
	
    // Initialize Array(2)
	for (int i = 0; i < size; i++)
		arr[i] = i % 5;
    
    // Start Timer (5)
	struct timeval start;
    gettimeofday(&start, NULL);
	
	// Thread creation
	int threadscount = 2;
	pthread_t threads[threadscount];
	
	pthread_create(&threads[0], NULL, countEven, (void*)&arrTemp);
	pthread_create(&threads[1], NULL, countOdd, (void*)&arrTemp);
	
    //Display
	printf("Evens: %d\n", arrStruct->evenCount);
    printf("Odds:  %d\n", arrStruct->oddCount);
    
	// Threads join
	for(int i=0; i<threadscount; i++)
        pthread_join(threads[i], NULL);
	
    // End Timer (5)
	struct timeval end;
    gettimeofday(&end, NULL);

    // Print Execution Time (5)
	long millis = getTimeDiff(start, end) / 1000;
    printf("Wall Time Taken: %ldms\n", millis );
	
	free(arr);
    return 0;
}