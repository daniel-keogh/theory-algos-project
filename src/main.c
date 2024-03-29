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
        .inputFile = NULL,
        .targetHash = NULL,
        .targetFile = NULL,
    };

    parse_opts(argc, argv, &options);

    // Get the result of the input file
    char* result = compute_hash(options.inputFile);

    if (options.targetFile != NULL) {
        // Compare the input file against the target file
        char* targetFileResult = compute_hash(options.targetFile);
        verify(result, targetFileResult);
    }
    else if (options.targetHash != NULL) {
        // Compare the input file against the target hash
        verify(result, options.targetHash);
    }
    else {
        puts(result);
    }

    return EXIT_SUCCESS;
}

void parse_opts(int argc, char* argv[], struct Options* options)
{
    // The first argument should be the input file (or "--help")
    if (argc > 1) {
        if (strcmp(argv[1], "--help") != 0) {
            try_set_file(argv[1], &options->inputFile);
        }
    }

    // Parse remaining user command line args using getopt_long()
    // Reference: <https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html>
    static struct option cliOptions[] = {
        {"help", no_argument, 0, 'h'},
        {"compare", required_argument, 0, 'c'},
        {"verify", required_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    int opt;
    int optIndex = 0;

    while ((opt = getopt_long(argc, argv, OPTS, cliOptions, &optIndex)) != -1) {
        switch (opt) {
            case 'c':
                try_set_file(optarg, &options->targetFile);
                break;
            case 'v':
                options->targetHash = malloc(sizeof(char) * (strlen(optarg) + 1));
                strcpy(options->targetHash, optarg);
                break;
            case 'h':
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                exit(EXIT_FAILURE);
        }
    }

    // Make sure an input file was given
    if (options->inputFile == NULL) {
        fprintf(stderr, "%s", RED("[Error] No input file specified.\n"));
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
}

void try_set_file(const char* path, char** dest)
{
    // Check if the file is readable
    // Reference: <https://stackoverflow.com/a/230068>
    if (access(path, R_OK) != -1) {
        *dest = malloc(sizeof(char) * (strlen(path) + 1));
        strcpy(*dest, path);
    }
    else {
        fprintf(stderr, RED("[Error] File: \"%s\" not found.\n"), path);
        exit(EXIT_FAILURE);
    }
}

char* compute_hash(const char* file)
{
    FILE* pfile = try_open_file(file);
    char* result = sha512(pfile);

    fclose(pfile);

    if (result == NULL) {
        fprintf(stderr, RED("[Error] Failed to read anything from file: \"%s\"\n"), file);
        exit(EXIT_FAILURE);
    }

    return result;
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
    printf("Usage: %s FILE [OPTIONS]\n\n", exec);
    printf("%s", "Options:\n");
    printf("%s", "  -h, --help\t\t\tPrint program usage information.\n");
    printf("%s", "  -c, --compare <file>\t\tCompare another file's hash against the input file's.\n");
    printf("%s", "  -v, --verify <hash>\t\tVerify the input file has the given hash.\n");
}
