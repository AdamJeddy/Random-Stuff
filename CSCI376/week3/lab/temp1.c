#include <stdio.h>
#define ARRAY_SIZE 100
#define THREADS 3

int main(){
    int partitionSize = ARRAY_SIZE/THREADS;
    for(int i=0; i<THREADS; i++){
        int startIndex = i*partitionSize;
        for(int j=0; j<partitionSize; j++){
            int value = j+startIndex;
            printf("%d ", value);
        }
        
        printf("\n");
    }

/*
    for(int i=0; i<THREADS; i++){
    int start = i*ARRAY_SIZE/THREADS;
    int end = (i+1)*ARRAY_SIZE/THREADS;
    for(int j=start; j<end; j++){
        printf("%d ", j);
    }

    printf("\n");
    }
*/
}