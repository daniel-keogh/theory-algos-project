#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>

#include "sha512.h"
#include "utils.h"
#include "main.h"

int main(int argc, char* argv[])
{
    struct Options options = {
        .filename = NULL,
        .target = NULL
    };

    parse_opts(argc, argv, &options);

    FILE* pfile = open_file(options.filename);

    char* result = sha512(pfile);

    if (options.target != NULL) {
        verify(result, options.target);
    }
    else {
        puts(result);
    }

    fclose(pfile);

    return EXIT_SUCCESS;
}

void parse_opts(int argc, char* argv[], struct Options* options)
{
    // Parse user command line args using getopt_long()
    // Reference: <https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html>
    static struct option cliOptions[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {"verify", required_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    int opt;
    int optIndex = 0;

    while ((opt = getopt_long(argc, argv, OPTS, cliOptions, &optIndex)) != -1) {
        switch (opt) {
            case 'f':
                // Check if the file is readable
                // Reference: <https://stackoverflow.com/a/230068>
                if (access(optarg, R_OK) != -1) {
                    options->filename = malloc(sizeof(char) * (strlen(optarg) + 1));
                    strcpy(options->filename, optarg);
                }
                else {
                    fprintf(stderr, RED("[Error] File: \"%s\" not found.\n"), optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'v':
                options->target = malloc(sizeof(char) * (strlen(optarg) + 1));
                strcpy(options->target, optarg);
                break;
            case 'h':
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                exit(EXIT_FAILURE);
        }
    }

    // Make sure a file was given
    if (options->filename == NULL) {
        fprintf(stderr, "%s", RED("[Error] No input file specified.\n"));
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
}

FILE* open_file(const char* filename)
{
    FILE* pFile;

    if ((pFile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s", RED("[Error] Failed to open the input file."));
        exit(EXIT_FAILURE);
    }

    return pFile;
}

void verify(const char* result, const char* target)
{
    // Do a case insensitive comparison 
    if (strcasecmp(result, target) == 0) {
        puts("OK");
    }
    else {
        printf("%s", YELLOW("=== Mismatch ===\n"));
        printf("%-128s  " RED("Result\n"), result);
        printf("%-128s  " GREEN("Target\n"), target);
    }
}

void usage(const char* exec)
{
    printf("Usage: %s [options]\n\n", exec);
    printf("%s", "Options:\n");
    printf("%s", "  -h, --help\t\t\tPrints some help text.\n");
    printf("%s", "  -f, --file <file>\t\tPath to the input file.\n");
    printf("%s", "  -v, --verify <hash>\t\tVerify a file has the given hash.\n");
}
