#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

struct arrStruct 
{
	long size;
	int oddCount, evenCount;
	int* array;
};

long int getTimeDiff(const struct timeval beg, const struct timeval end){
    return (end.tv_sec - beg.tv_sec) * 1000000 +  end.tv_usec - beg.tv_usec;
}


void* countOdd(void* params)
{
    struct arrStruct* data = (struct arrStruct*)params;
	data->oddCount = 0;

	for(int i = 0; i < data->size; i++)
		if (data->array[i] % 2 == 1)
			data->oddCount++;
}

void* countEven(void* params)
{
    struct arrStruct* data = (struct arrStruct*)params;
	data->evenCount = 0;
	
	for(int i = 0; i < data->size; i++)
		if (data->array[i] % 2 == 0)
			data->evenCount++;
}

int main(){
    // Create Array (1)
	long size = 100000000;
    int* arrTemp = (int*)malloc(size * sizeof(int));
	
	struct arrStruct arr = {size, 0, 0, arrTemp};
	
    // Initialize Array(2)
	for (int i = 0; i < size; i++)
		arrTemp[i] = i % 5;
    
    // Start Timer (5)
	struct timeval start;
    gettimeofday(&start, NULL);
	
	// Thread creation
	int threadscount = 2;
	pthread_t threads[threadscount];
	
	pthread_create(&threads[0], NULL, countEven, (void*)&arr);
	pthread_create(&threads[1], NULL, countOdd, (void*)&arr);
    
	// Threads join
	for(int i=0; i<threadscount; i++)
        pthread_join(threads[i], NULL);
        
    //Display
	printf("Evens: %d\n", arr.evenCount);
    printf("Odds:  %d\n", arr.oddCount);
	
    // End Timer (5)
	struct timeval end;
    gettimeofday(&end, NULL);

    // Print Execution Time (5)
	long millis = getTimeDiff(start, end) / 1000;
    printf("Wall Time Taken: %ldms\n", millis );
	
	free(arrTemp);
    return 0;
}