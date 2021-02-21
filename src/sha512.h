#ifndef SHA512_H_INCLUDED
#define SHA512_H_INCLUDED

#include <inttypes.h>

#define WORD_SIZE       32
#define WORD            uint32_t
#define PF              PRIX32

#define Ch(x, y, z)     ((x) & (y)) ^ (~(x) & (z))
#define Maj(x, y, z)    ((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z))

#define SHR(x, n)       (x) >> (n)
#define ROTR(x, n)      SHR((x), (n)) | ((x) << (WORD_SIZE - (n)))

#define UP_SIG_0(x)     ROTR((x), 2) ^ ROTR((x), 13) ^ ROTR((x), 22)
#define UP_SIG_1(x)     ROTR((x), 6) ^ ROTR((x), 11) ^ ROTR((x), 25)

#define LOW_SIG_0(x)    ROTR((x), 7) ^ ROTR((x), 18) ^ SHR((x), 3)    
#define LOW_SIG_1(x)    ROTR((x), 17) ^ ROTR((x), 19) ^ SHR((x), 10)

char* compute(const char* filename);
void bin_print(unsigned int i);

#endif
