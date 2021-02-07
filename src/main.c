#include <stdio.h>

#include "main.h"

int main(int argc, char *argv[]) {
    int i = 0xf1;

    printf("Original:  ");
    bin_print(i);
    printf("\n");

    for (int j = 0; j < 40; j++) {
        printf("%3d << %2d: ", i, j);
        bin_print(i << j);
        printf("\n");
    }

    return 0;
}

void bin_print(int i) {
    // Number of bis in an integer.
    int j = (sizeof(int) * 8) - 1;

    for (; j >= 0; j--) {
        int k = ((1 << j) & i) ? 1 : 0;
        printf("%d", k);
    }
}
