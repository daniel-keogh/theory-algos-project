#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "sha512.h"
#include "main.h"

int main(int argc, char* argv[])
{
    char* filename = NULL;
    parse_opts(argc, argv, &filename);

    FILE* pfile = open_file(filename);

    // char* result = sha512(pfile);
    // puts(result);

    fclose(pfile);

    return EXIT_SUCCESS;
}

void parse_opts(int argc, char* argv[], char** filename)
{
    // Parse user command line args using getopt_long()
    // Reference: <https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html>
    static struct option options[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    int opt;
    int optIndex = 0;

    while ((opt = getopt_long(argc, argv, OPTS, options, &optIndex)) != -1) {
        switch (opt) {
            case 'f':
                // Check if the file is readable
                if (access(optarg, R_OK) != -1) {
                    *filename = malloc(sizeof(char) * (strlen(optarg) + 1));
                    strcpy(*filename, optarg);
                }
                else {
                    fprintf(stderr, "[Error] File: \"%s\" not found.\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                exit(EXIT_FAILURE);
        }
    }

    // Make sure a file was given
    if (*filename == NULL) {
        fprintf(stderr, "%s", "[Error] No input file specified.\n");
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
}

FILE* open_file(const char* filename)
{
    FILE* pFile;

    if ((pFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s", "[Error] Failed to open the input file.\n");
        exit(EXIT_FAILURE);
    }

    return pFile;
}

void usage(const char* exec)
{
    printf("Usage: %s [options]\n\n", exec);
    printf("%s", "Options:\n");
    printf("%s", "  -h, --help\t\tPrints some help text.\n");
    printf("%s", "  -f, --file <file>\tPath to the input file.\n");
}
