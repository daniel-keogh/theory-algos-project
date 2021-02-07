#include <stdio.h>

#include "main.h"

int main(int argc, char *argv[]) {
    // Set i to a literal value
    unsigned int i = 0x0f0f0f0f;

    printf("Original:\t");
    // Print i in binary
    bin_print(i);
    // End line
    printf("\t%x\t%u\n\n", i, i);

    // 32
    int j = (sizeof(unsigned int) * 8) - 1;

    for (; j >= 0; j--) {
        // 1 shifted left j times
        bin_print(1 << j);
        printf("\n");

        // i
        bin_print(i);
        printf("\n-------------------------------- &\n");

        // (1 shifted left j times) bitwise logical and i
        bin_print((1 << j) & i);
        printf("\n\n");
    }

    return 0;
}

void bin_print(unsigned int i) {
    // Number of bis in an integer.
    int j = (sizeof(unsigned int) * 8) - 1;

    for (; j >= 0; j--) {
        // Pick out the j^th bit of i
        int k = ((1 << j) & i) ? 1 : 0;
        printf("%d", k);
    }
}
