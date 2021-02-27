#ifndef SHA512_H_INCLUDED
#define SHA512_H_INCLUDED

#include <inttypes.h>

#define WORD_SIZE       64
#define PF              PRIX64

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

char* compute(const char* filename);

#endif
