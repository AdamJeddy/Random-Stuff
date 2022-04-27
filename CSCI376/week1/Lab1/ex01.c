#include <string.h>
#include <stdio.h>

int main(){
    const char* fname = "John";
    const char* lname = "Smith";

    char buffer[256];
    strcpy(buffer, fname);
    strcat(buffer, " ");
    strcat(buffer, lname);

    printf("%s\n", buffer);
    return 0;
}
