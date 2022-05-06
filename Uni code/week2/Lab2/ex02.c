#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long int getTimeDiff(const struct timeval beg, const struct timeval end){
    return (end.tv_sec - beg.tv_sec) * 1000000 +  end.tv_usec - beg.tv_usec;
}

int countOdd(int* arr, int size){
    // To Complete (3)
	int count = 0;
	
	for(int i = 0; i < size; i++)
		if (arr[i] % 2 == 1)
			count++;
	
	return count;
}

int countEven(int* arr, int size){
    // To Complete (4)
	int count = 0;
	
	for(int i = 0; i < size; i++)
		if (arr[i] % 2 == 0)
			count++;
	
	return count;
}

int main(){
    // Create Array (1)
	int size = 100000000;
    int* arr = (int*)malloc(size * sizeof(int));
	
    // Initialize Array(2)
	for (int i = 0; i < size; i++)
		arr[i] = i % 5;
    
    // Start Timer (5)
	struct timeval start;
    gettimeofday(&start, NULL);


    printf("Evens: %d\n", countEven(arr, size));
    printf("Odds:  %d\n", countOdd(arr, size));
    
    // End Timer (5)
	struct timeval end;
    gettimeofday(&end, NULL);

    // Print Execution Time (5)
	long millis = getTimeDiff(start, end) / 1000;
    printf("Wall Time Taken: %ldms\n", millis );
	
	free(arr);
    return 0;
}
