#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

FILE* try_open_file(const char* filename)
{
    FILE* pFile;

    if ((pFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, RED("[Error] Failed to open file: \"%s\"\n"), filename);
        exit(EXIT_FAILURE);
    }

    return pFile;
}
