#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "sha512.h"
#include "main.h"

int main(int argc, char *argv[])
{
    char* filename = NULL;
    parseOpts(argc, argv, &filename);

    puts(filename);

    // compute(filename);

    return EXIT_SUCCESS;
}

void parseOpts(int argc, char* argv[], char** filename)
{
    /* Parse user command line args using getopt_long()
     * Reference: <https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html>
     */
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    int opt;
    int optionIndex = 0;

    while ((opt = getopt_long(argc, argv, OPTS, long_options, &optionIndex)) != -1) {
        switch (opt) {
            case 'f':
                // Check if the file is readable
                if (access(optarg, R_OK) != -1) {
                    *filename = malloc(sizeof(char) * (strlen(optarg) + 1));
                    strcpy(*filename, optarg);
                } else {
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

    if (filename == NULL) {
        fprintf(stderr, "%s", "[Error] No input file specified.\n");
        exit(EXIT_FAILURE);
    }
}

void usage(const char* exec)
{
    printf("Usage: %s [options]\n\n", exec);
    printf("%s", "Options:\n");
    printf("%s", "  -h, --help\t\tPrints some help text.\n");
    printf("%s", "  -f, --file <file>\tPath to the input file.\n");
}
