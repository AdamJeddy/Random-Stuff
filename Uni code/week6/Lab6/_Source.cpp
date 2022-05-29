#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 

#define CLEAR_STDIN for (char c; (c = getchar()) != '\n' && c != EOF;) {}

int main() {
    unsigned int num;
    char ch;

    printf("Enter a number: ");
    scanf("%d", &num);
    CLEAR_STDIN;

    printf("Enter a character: ");
    scanf("%c", &ch);

    printf("~~ %d %c ~~", num, ch);
	return 0;
}