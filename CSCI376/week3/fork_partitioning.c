#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() 
{
    pid_t pid;
    pid_t pid_of_parent = getppid();

    int start, end, number_of_files_to_delete = 10, number_of_processes = 3;

    for (int i = 0; i < number_of_processes; i++)
    {
        if (pid_of_parent == getpid())
        {
            start = i * number_of_files_to_delete / number_of_processes;
            end = (i + 1) * number_of_files_to_delete / number_of_processes;
            pid = fork();
        }
        else // Children get out of the loop
            break;
    }
    
    /* Only children will do the work: delete files */
    if (pid == 0)
    {
        char buffer[50];
        for (int i = start; i < end; i++)
        {
            sprintf(buffer, "file/file_number_%d", i);
            printf("%s", buffer);
            // Delete the files
            if (remove(buffer) == 0)
                printf("File deleted successfully");
            else
                printf("Unable to delete the file");
        }
        
    }

    /* Parents have to wait for children to finish */
    if (pid_of_parent == getpid())
    {
        for (int i = 0; i < number_of_processes; i++)
            wait(NULL);
        printf("All files have been deleted\n");
    }

    return 0;
}