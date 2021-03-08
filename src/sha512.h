#ifndef SHA512_H_INCLUDED
#define SHA512_H_INCLUDED

#include <inttypes.h>

#define PF              PRIX64
#define WORD_SIZE       64
#define BLOCK_SIZE      128

#define Ch(x, y, z)     ((x) & (y)) ^ (~(x) & (z))
#define Maj(x, y, z)    ((x) & (y)) ^ ( (x) & (z)) ^ ((y) & (z))

#define SHR(x, n)       (x) >> (n)
#define ROTR(x, n)      SHR((x), (n)) | ((x) << (WORD_SIZE - (n)))
#define ROTL(x, n)      ((x) <<  (n)) | ((x) >> (WORD_SIZE - (n)))

#define CAP_SIG_0(x)    ROTR((x), 28) ^ ROTR((x), 34) ^ ROTR((x), 39)
#define CAP_SIG_1(x)    ROTR((x), 14) ^ ROTR((x), 18) ^ ROTR((x), 41)
#define LOW_SIG_0(x)    ROTR((x),  1) ^ ROTR((x),  8) ^  SHR((x),  7)
#define LOW_SIG_1(x)    ROTR((x), 19) ^ ROTR((x), 61) ^  SHR((x),  6)

typedef uint64_t Word;
typedef uint8_t  Byte;

union Block {
    Byte bytes[BLOCK_SIZE];
    Word words[32];
};

char* compute(const char* filename);
void readfile(const char* filename);

#endif
