#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

#include "sha512.h"
#include "utils.h"

#define PATH(filename)  "tests/files/" filename

void test_correct();
void test_incorrect();
void test_not_empty();
void test_empty_file();

int main(int argc, char* argv[])
{
    puts(YELLOW("Running tests...\n"));

    test_correct();
    test_incorrect();
    test_not_empty();
    test_empty_file();

    puts(GREEN("\nAll tests passed."));

    return EXIT_SUCCESS;
}

void test_correct()
{
    printf(YELLOW("test_correct..."));

    char* expected = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";

    FILE* pfile = open_file(PATH("abc.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(strcasecmp(result, expected) == 0);

    puts(GREEN("\t\tPASSED"));
}

void test_incorrect()
{
    printf(YELLOW("test_incorrect..."));

    char* expected = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";

    FILE* pfile = open_file(PATH("def.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(strcasecmp(result, expected) != 0);

    puts(GREEN("\tPASSED"));
}

void test_empty_file()
{
    printf(YELLOW("test_empty_file..."));

    FILE* pfile = open_file(PATH("empty.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(result == NULL);

    puts(GREEN("\tPASSED"));
}

void test_not_empty()
{
    printf(YELLOW("test_not_empty..."));

    FILE* pfile = open_file(PATH("abc.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(result != NULL);

    puts(GREEN("\tPASSED"));
}
