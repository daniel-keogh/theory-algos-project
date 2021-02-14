#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/* Command line option string. */
#define OPTS "f:h"

/* Parse the user's provided command-line arguments. */
void parseOpts(int argc, char* argv[], char** filename);

/* Output program usage information. */
void usage(const char* exec);

#endif
