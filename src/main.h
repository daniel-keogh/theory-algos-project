#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/* Command line option string. */
#define OPTS "f:h"

/* Parse the user's provided command-line arguments. */
void parse_opts(int argc, char* argv[], char** filename);

/* Opens the file with the given path and returns a pointer to it. */
FILE* open_file(const char* filename);

/* Output program usage information. */
void usage(const char* exec);

#endif
