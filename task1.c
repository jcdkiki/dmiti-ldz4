#include <stdio.h>
#include "common.h"

int main()
{
    int ones = 0;
    int n = 100000;
    for (int i = 0; i < n; i++) {
        ones += random_bit(0.7);
    }

    printf("Total tests: %d\n", n);
    printf("Ones: %d\n", ones);
    printf("Zeroes: %d\n", n - ones);
}
