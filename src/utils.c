#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

FILE* open_file(const char* filename)
{
    FILE* pFile;

    if ((pFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s", RED("[Error] Failed to open the input file."));
        exit(EXIT_FAILURE);
    }

    return pFile;
}
