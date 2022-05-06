#include <stdio.h>

int main() {
    char buffer[256];
    int  age;

    printf("What is your name?\n");
    scanf("%s", buffer);
    printf("What is your age?\n");
    scanf("%d", &age);
    printf("Hi %s, you are %d years old.\n", buffer, age);

    return 0;
}