#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populateArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("Enter value %d: ", ++i);
        scanf("%d", &arr[--i]);
    }
}

void print(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("| %d ", arr[i]);
    printf("|");
}

void printHalf1(int* arr, int size)
{
    printf("\nFirst Half of the Array:\n");
    for (int i = 0; i < size / 2; i++)
        printf("| %d ", arr[i]);
    printf("|");
}

void printHalf2(int* arr, int size)
{
    printf("\nOther Half of the Array:\n");
    for (int i = size / 2; i < size; i++)
        printf("| %d ", arr[i]);
    printf("|");
}

int main() {
    // Create a dynamic array of integers with an even size entered by the user
    printf("Enter size of array?\n> ");
    int size;
    scanf("%d", &size);
    if (size < 0)
        size = 2;
    if (size % 2 == 1)
        printf("Size not even so bumped up by 1, %d\n", ++size);
    printf("Array size: %d\n", size);

    int* arr = (int*)malloc(size * sizeof(int));

    // Populate the array with numbers using scanf() from <stdio.h>.
    populateArr(arr, size);

    // Create a function to prints the contents of an integer array:  print(int* arr, int size)
    print(arr, size);

    // Print out the first half and second half of the array separately
    printHalf1(arr, size);
    printHalf2(arr, size);


    free(arr);
    return 0;
}