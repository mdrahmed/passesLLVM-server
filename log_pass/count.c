#include <stdio.h>
int count = 0;

void foo(char* test) {
    count++;
    printf("count = %d\n", count);
}
