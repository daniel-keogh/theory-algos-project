# Theory of Algorithms Project

Y4S2 Theory of Algorithms Project

## Description

A C program that calculates & outputs the SHA-512 digest of a given input file.

## Compilation

### Prerequisites

First make sure you have the following installed on your system.

- `gcc`
- `make`

After cloning the repository, you can compile and run the program as follows:

```sh
$ make
$ ./sha512 [options]
```

### Options

| Option              | Description             |
| ------------------- | ----------------------- |
| `-h, --help`        | Prints some help text.  |
| `-f, --file <file>` | Path to the input file. |

<!-- #### Example

```sh
$ ./sha512 -f input.txt

``` -->

### Testing

```sh
$ make test
```

## What is SHA-512 & Why is it Important?

The Secure Hash Algorithm (SHA) functions were originally developed by the US National Institute of Standards and Technology (NIST) and published in 1993 as SHA-0, but subsequently revised with the release of SHA-1 in 1995 [1]. SHA-2 is the successor to SHA-1 and is a family of 4 hash functions, with the most complex being SHA-512, so-called because it produces an output 512 bits in length [1].

SHA-512 is an example of a cryptographic hash function. That is, a function which can read in a message and compute a fixed-length string (or _digest_) which can be seen as a unique representation of that message, much like a fingerprint [2]. The motivation for hash functions like SHA-512 over digital signature schemes like RSA, lies in their ability to produce a short, fixed-length digest for messages of arbitrary length. In other words, even if we had a message that is hundreds of megabytes in size, it should still be relatively fast to compute its digest. This is in contrast to algorithms like RSA where the length of the plaintext is limited [2].

An important characteristic of hash functions like SHA-512 is they are highly sensitive to all input bits [2]. This means that even minor alterations to the message will result in a vastly different digest being produced. This is called the avalanche effect [6]. For example, below the input "abc" produces a SHA-256 output that is markedly distinct from the string "abb", despite only a single letter being modified.

<div align="center">
  <img src="https://user-images.githubusercontent.com/37158241/111521283-decc5a80-8750-11eb-91ed-b04bcbced56f.png" />
</div>

As a result of this property, hash functions like SHA-512 have found important application in the creation of digital signatures and in verifying the integrity of messages, e.g. by providing a way to ensure digital files have not been modified [1]. Just some of the many other real-world use cases of hash functions include the Git revision control system, which uses them to identify files being tracked in a repository [1]. Meanwhile SHA-512's sibling algorithm, SHA-256, is used in popular authentication and encryption protocols, including SSL, TLS, IPsec, SSH, and PGP [3]. In Linux systems, SHA-256 is also used for hashing passwords, while cryptocurrencies like Bitcoin use it for verifying transactions [3].

## Q & A

**_Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?_**

One of the main distinctions between hashing and encryption is reversability. Encryption algorithms often require both an input as well as a key in order to generate the output (or ciphertext). This process is reversible as anyone able to obtain the key will also be able to decrypt the ciphertext and therein view the original message [4]. In contrast, SHA-512, like all algorithms specified in NIST FIPS 180-4 are "one-way hash functions" [5]. It is therefore not required for the specific hash algorithm used to be kept secret because the digest cannot be converted back to its original form [4]. However, while it is not technically possible to reverse a hash in order to retrieve the original message, hash algorithms like SHA-512 are still susceptible to collisions - where two messages produce the same hash.

A central characteristic of any secure hash function like SHA-512 is that of "preimage resistance", also referred to as "one-wayness". This means that for any given hash, it must be computationally infeasible to find a message that will produce the same hash output [2]. Meanwhile, a second property of hash functions is that of "second preimage resistance", also referred to as (weak) collision resistance. This means that for hash algorithms like SHA-512, it should be infeasible to create two distinct plaintext messages that produce the exact same digest [2]. These are crucial characteristics of hash algorithms as they are widely used for verifying digital files and deriving cryptographic keys. If a bad actor were able to feasibly construct a message that produces the same hash output, they could perform substitution attacks, replacing a file with another malicious file that produces the same digest [2].

It is not possible to design a hash function that is fully resistant to collisions. This is because the input to a hash function is theoretically infinite, while the digest will always be the same length. For this reason, it must be true that multiple inputs will inevitably produce the same hash value [2]. This is illustrated by the _Pigeonhole Principle_, which states that if a pigeon loop were to contain 100 birds but only 99 holes, at least one hole must be occupied by two birds [2]. Because every hash algorithm produces an output with a fixed number of bits (_n_), there are 2<sup>_n_</sup> possible digests that can be computed by that algorithm, while there is an infinite number of possible inputs [2] (in the case of SHA-512 there are 2<sup>512</sup> possible outputs). In other words, there are an infinite number of possible inputs that can produce the same output. Because of this, even given unlimited computing power it is not possible to retrieve the _exact_ message that produced a given hash value as there are so many inputs that could produce the same hash [1]. It would of course be possible to determine _some_ possible messages that produce that hash (i.e. collisions), given enough time and resources, but it would not be possible to determine precisely what input was fed to the algorithm originally [1].

**_Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?_**

As mentioned previously, secure hash algorithms should be "preimage resistant". A preimage of a given hash value (`H`), is any message (`M`) that when run through the hash algorithm will produce the value of `H` [1]. In other words, a preimage is any message wherein `Hash(M) == H` [1]. Preimages are distinct from collisions, which is where two distinct input messages produce the same hash.

If given a hash value, one can search for preimages using a brute force technique which involves continuously checking the hash output of different messages until eventually finding a message that produces the same output as the target hash. The below C code is adapted from the pseudo-code shown on page 174 of [1]. Here, the `find_preimage` function takes a SHA-512 hash (called `target`), and will iteratively try to find the SHA-512 hash of a random plaintext message (`m`). It will then use `strcmp` to check if the hash of that message (`hash_m`) equals the hash value passed into the function. If so, the function will return the matching input message (`m`), or otherwise continue looping until a match is found.

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Finds a preimage of `target` using brute-force. */
char* find_preimage(const char* target)
{
    while (true) {
        char* m = some_message();
        char* hash_m = sha512(m);

        if (strcmp(hash_m, target) == 0) {
            return m; // found preimage
        }
    }
}
```

If given enough time, and provided with each of the 512-bit strings starting from `"0" * 128`, up to `"f" * 128`, this function will return an input message for each of the possible 512-bit strings. 

In the code below, the `for` loop (in which the `find_preimage` function is called), executes once for each SHA-512 string in the `targets[]` array. The result is then printed to the screen. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

int main(void)
{
    // array of all SHA-512 output strings
    char* targets[] = {
        "0000...",
        // ......,
        "ffff...",
    };

    // the total number of hashes that can be produced by SHA-512 (2^512)
    uint64_t num_hashes = (uint64_t)pow(2, 512);

    // for each hash in targets[], try and brute-force a preimage
    for (int i = 0; i < num_hashes; i++) {
        char* result = find_preimage(targets[i]);
        puts(result);
    }

    return EXIT_SUCCESS;
}
```

However, this sort of brute force attack wherein we try as many possible inputs in order to find a message corresponding to a given digest would require 2<sup>L</sup> evaluations, where L is the length of the digest (for SHA-512 that is 512 bits) [6]. Such a technique can therefore be considered wildly impractical due to the length of time it would take to successfully find an input message, as explained in [7].

**_How difficult is it to find a hash digest beginning with at least twelve zeros?_**

## References

1. Jean-Philippe Aumasson. _Serious cryptography: a practical introduction to modern encryption_. Chapter 6 – Hash Functions. No Starch Press, 2017. ISBN: 978-1-59327-826-7.

2. Christof Paar and Jan Pelzl. _Understanding cryptography: a textbook for students and practitioners_. Chapter 11 - Hash Functions. Springer Science & Business Media, 2009, ISBN: 978-3-642-04101-3. DOI: [10.1007/978-3-642-04101-3](https://doi.org/10.1007/978-3-642-04101-3).

3. [_SHA-256 Algorithm Overview_](https://www.solarwindsmsp.com/blog/sha-256-encryption). SolarWinds MSP. 12 Sep, 2019.

4. [_Hashing explained: Why it's your best bet to protect stored passwords_](https://www.csoonline.com/article/3602698/hashing-explained-why-its-your-best-bet-to-protect-stored-passwords.html). CSO Online. Lucian Constantin. Jan 13, 2021.

5. Quynh H. Dang. _Secure Hash Standard_. Federal Inf. Process. Stds. (NIST FIPS) - 180-4. Gaithersburg, MD: US Department of Commerce, National Institute of Standards and Technology, Aug. 2015. DOI: [10.6028/NIST.FIPS.180-4](https://doi.org/10.6028/NIST.FIPS.180-4).

6. [_Secure Hash Algorithms_](https://brilliant.org/wiki/secure-hashing-algorithms/) Brilliant.

7. [Why haven't any SHA-256 collisions been found yet?](https://crypto.stackexchange.com/a/47810). user47922. StackExchange Cryptography. May 29 2017.
