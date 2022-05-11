#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#define ARRAY_SIZE 1000
#define CHILD_COUNT 2

// Global variable
sem_t *mySem;
int count;
int *arr;

// Clears a previously created semaphore
void clear_semaphore(const char *name)
{
    // Test if the semaphore can be opened
    sem_t *sem = sem_open(name, 0);

    // If the semaphore failed to open, it's closed or doesn't exist
    if (sem == SEM_FAILED)
    {
        printf("There is no semaphore with name \"%s\"\n", name);
    }
    else
    {
        // If the semaphore does exist, then
        // Close the semaphore
        if (sem_close(sem) == -1)
        {
            printf("Failed to close semaphore \"%s\"\n", name);
            // exit(EXIT_FAILURE);
            return;
        }
        // Unlink the semaphore
        if (sem_unlink(name) == -1)
        {
            printf("Failed to unlink semaphore \"%s\"\n", name);
            // exit(EXIT_FAILURE);
            return;
        }
        printf("Successfully cleared semaphore \"%s\"\n", name);
    }
}

int main()
{
    // Opening a file that the processes will print into
    FILE *file = fopen("list1.txt", "w");

    // Initialize the array to 1 from start to finish
    arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = 1;
    }

    // Opening a semaphore is necessary before using it
    // O_CREAT means create a new semaphore if one doesn't exist
    // const char *name = "/semName";
    mySem = sem_open("/semName", O_CREAT, 0666, 1);

    pid_t children[CHILD_COUNT];
    memset(children, 0, CHILD_COUNT * sizeof(pid_t));

    for (int i = 0; i < CHILD_COUNT; i++)
    {
        children[i] = fork();

        // If the ID is 0, it means a child process
        if (children[i] == 0)
        {
            for (int j = 0; j < ARRAY_SIZE; j++)
            {
                sem_wait(mySem); // Lock
                fprintf(file, "Proc %d - Elem %d - Value %d\n", i, j, arr[j]);
                fflush(file);
                sem_post(mySem); // Unlock
            }
        }
    }

    // Closing and Unlinking the semaphore are both necessary to free it
    sem_close(mySem);
    sem_unlink("/semName");

    fclose(file);
    free(arr);
}
