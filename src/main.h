#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/* Command line option string. */
#define OPTS "f:v:h"

 /* Options passed through the CLI. */
struct Options {
    char* filename;
    char* target;
};

/* Parse the user's provided command-line arguments. */
void parse_opts(int argc, char* argv[], struct Options* options);

/* Opens the file with the given path and returns a pointer to it. */
FILE* open_file(const char* filename);

/* Verify whether or not two hashes are the same string. */
void verify(const char* result, const char* target);

/* Output program usage information. */
void usage(const char* exec);

#endif
