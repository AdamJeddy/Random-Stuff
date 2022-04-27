#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    pid_t pid;
    int i, pStart = 0, cStart = 100, end = 200;
    char buffer[100], num[10];
    char* temp;
    strcat(buffer, "file/file_number_");
    pid = fork(); // new process created

    if (remove("file/file_number_1") == 0)
        printf("File deleted successfully");
    else
        printf("Unable to delete the file");

    if (pid > 0) /* parent */
    {
        for (int i = pStart; i < end; i++)
        {
            itoa(i, num, 10);
            temp = strcat(buffer, num);
            if (remove(temp) == 0)
                printf("File deleted successfully");
            else
                printf("Unable to delete the file");
        }
    }
    else /* child */
    {
        for (int i = pStart; i < end; i++)
        {
            itoa(i, num, 10);
            temp = strcat(buffer, num);
            if (remove(temp) == 0)
                printf("File deleted successfully");
            else
                printf("Unable to delete the file");
        }
    }

    return 0;
}