#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#include "sha512.h"
#include "utils.h"

#define PATH(filename)  "./tests/files/" filename

void test_correct();
void test_distinct();
void test_not_empty();
void test_empty_file();
void test_hash_length();

int main(int argc, char* argv[])
{
    puts(YELLOW("Running tests...\n"));

    test_correct();
    test_distinct();
    test_empty_file();
    test_not_empty();
    test_hash_length();

    puts(GREEN("\nAll tests passed."));

    return EXIT_SUCCESS;
}

/* Tests that a given file produces the expected hash */
void test_correct()
{
    printf(YELLOW("test_correct..."));

    char* expected = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";

    FILE* pfile = open_file(PATH("abc.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(strcasecmp(result, expected) == 0);

    puts(GREEN("\t\t\tPASSED"));
}

/* Tests that two different files will produce distinct hashes */
void test_distinct()
{
    printf(YELLOW("test_distinct..."));

    char* expected = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";

    FILE* pfile_a = open_file(PATH("abc.txt"));
    char* result_a = sha512(pfile_a);
    fclose(pfile_a);

    FILE* pfile_b = open_file(PATH("def.txt"));
    char* result_b = sha512(pfile_b);
    fclose(pfile_b);

    assert(strcasecmp(result_a, result_b) != 0);

    puts(GREEN("\t\tPASSED"));
}

/* Tests that an empty file will return NULL */
void test_empty_file()
{
    printf(YELLOW("test_empty_file..."));

    FILE* pfile = open_file(PATH("empty.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(result == NULL);

    puts(GREEN("\t\tPASSED"));
}

/* Tests that a file that isn't empty doesn't return NULL */
void test_not_empty()
{
    printf(YELLOW("test_not_empty..."));

    FILE* pfile = open_file(PATH("abc.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(result != NULL);

    puts(GREEN("\t\tPASSED"));
}

/* Tests that a file's computed hash is 128 characters long */
void test_hash_length()
{
    printf(YELLOW("test_hash_length..."));

    FILE* pfile = open_file(PATH("abc.txt"));
    char* result = sha512(pfile);
    fclose(pfile);

    assert(strlen(result) == 128);

    puts(GREEN("\t\tPASSED"));
}
