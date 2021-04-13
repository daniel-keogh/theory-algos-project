#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/* Command line option string. */
#define OPTS "c:v:h"

 /* Options passed through the CLI. */
struct Options {
    char* inputFile;
    char* targetHash;
    char* targetFile;
};

/* Parse the user's provided command-line arguments. */
void parse_opts(int argc, char* argv[], struct Options* options);

/* Checks if `path` points to a file and if so, allocates it to `dest`.
 * Quits the program if the file is not accessible.
*/
void try_set_file(const char* path, char** dest);

/* Verify whether or not two hashes are the same string. */
void verify(const char* result, const char* target);

/* Output program usage information. */
void usage(const char* exec);

#endif
