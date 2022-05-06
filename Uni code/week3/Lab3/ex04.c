#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 50
#define PARTITIONS 5
#define PARTITION_SIZE (SIZE/PARTITIONS)

struct arr{
    int beg, end;  // Input values
};

int main()
{
    struct arr params[SIZE];
    pid_t pid[PARTITIONS];

    // Create an array with 100 ints
    int arr[SIZE];

    // Initialize the array
    for (int i = 0; i < SIZE; i++)
        arr[i] = i+1;
    
    // Partition the array into 5 equally sized parts
    for(int i = 0; i < PARTITIONS; i++){
        params[i].beg = i * PARTITION_SIZE;
        params[i].end = (i+1) * PARTITION_SIZE;
    }

    for (int i = 0; i < PARTITIONS; i++)
        printf("Partition %d :\n\tStart: %d\n\tEnd: %d\n", i, params[i].beg, params[i].end);
    

    // Start 5 child processes, each incrementing the elements by 1    
    for (int i = 0; i < PARTITIONS; i++)
    {
        // Create array
        pid[i] = fork();

        // Work for child
        if (pid[i] == 0)
        {
            for (int i = params[i].beg; i < params[i].end; i++)
                arr[i]++;
            for (int i = 0; i < SIZE; i++)
                printf("%d ", arr[i]);
            printf(" The Child Process %d Finished\n", i);
            return 0;
        }
    }
    

    // Wait for the processes to finish and print
    for (int i = 0; i < PARTITIONS; i++)
    {
        printf("PID %d: %d\n", i, pid[i]);
        waitpid(pid[i], NULL, WUNTRACED);
    }

    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
    return 0;
}