#ifndef SHA512_H_INCLUDED
#define SHA512_H_INCLUDED

#include <inttypes.h>

#define PF              PRIx64
#define BYTE_SIZE       8
#define WORD_SIZE       64
#define BLOCK_SIZE      128
#define ZERO_BIT        0x00
#define ONE_BIT         0x80

#define Ch(x, y, z)     (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z)    (((x) & (y)) ^ ( (x) & (z)) ^ ((y) & (z)))

#define SHR(x, n)       ((x) >> (n))
#define ROTR(x, n)      (SHR((x), (n)) | ((x) << (WORD_SIZE - (n))))
#define ROTL(x, n)      (((x) <<  (n)) | ((x) >> (WORD_SIZE - (n))))

#define CAP_SIG_0(x)    (ROTR((x), 28) ^ ROTR((x), 34) ^ ROTR((x), 39))
#define CAP_SIG_1(x)    (ROTR((x), 14) ^ ROTR((x), 18) ^ ROTR((x), 41))
#define LOW_SIG_0(x)    (ROTR((x),  1) ^ ROTR((x),  8) ^  SHR((x),  7))
#define LOW_SIG_1(x)    (ROTR((x), 19) ^ ROTR((x), 61) ^  SHR((x),  6))

// Determine endianness at runtime
// Reference: <https://developer.ibm.com/technologies/systems/articles/au-endianc/>
extern const int _i;
#define is_lilend       ((*(char*) & _i) != 0)

typedef uint64_t Word;
typedef uint8_t Byte;

/* SHA-512 works in blocks of 1024 bits. */
union Block {
    Byte bytes[BLOCK_SIZE];
    Word words[32];
    Word sixf[16];
};

/* For keeping track of where we are with the input message/padding. */
enum Status {
    READ,
    PAD,
    END
};

/* Computes the SHA-512 digest of a file. */
char* sha512(FILE* file);

/* Returns 1 if a new block was created from the original message or padding.
 * Returns 0 if all of the padded message has already been consumed.
 */
int next_block(FILE* file, union Block* block, enum Status* S, Word* numBits);

/* Performs SHA-512 hash computation as specified in section 6.4.2. */
void next_hash(union Block* M, Word* H);

#endif
