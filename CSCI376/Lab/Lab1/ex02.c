#include <stdio.h>
#include <stdlib.h>

int main() {
    int num = 0, count = 0, sum = 0;
    FILE* in = fopen("input.txt", "r");
    while (!feof(in)) {
        fscanf(in, "%d", &num);
        if(!feof(in)){
            count++;
            sum += num;
        }
    }

    FILE* out = fopen("output.txt", "w");
    fprintf(out, "The sum of the %d numbers in the file is %d", count, sum);

    fclose(in);
    fclose(out);
    return 0;
}
