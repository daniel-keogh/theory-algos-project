# Theory of Algorithms Project

Y4S2 Theory of Algorithms Project

## Description

A C program that calculates & outputs the SHA-512 digest of a given input file, in accordance with the [NIST FIPS 180-4](https://doi.org/10.6028/NIST.FIPS.180-4) specification.

## Compilation

### Prerequisites

First make sure you have the following installed on your system.

- `gcc`
- `make`

Both of these can be installed on Debian-based systems by running the following:

```sh
$ sudo apt install build-essential
```

After cloning the repository, you can then compile and run the program as follows:

```sh
$ make
$ ./sha512 [options]
```

### Options

| Option              | Description             |
| ------------------- | ----------------------- |
| `-h, --help`        | Prints some help text.  |
| `-f, --file <file>` | Path to the input file. |

#### Example

```sh
$ ./sha512 -f input.txt
ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f
```

### Installation

To install the executable for system-wide use, you could run:

```sh
$ make
$ sudo make install
```

#### Uninstalling

```sh
$ sudo make uninstall
```

## Testing

You can test the program by running the following:

```sh
$ make test
```

## What is SHA-512 & Why is it Important?

The Secure Hash Algorithm (SHA) functions were originally developed by the US National Institute of Standards and Technology (NIST) and published in 1993 as SHA-0, but subsequently revised with the release of SHA-1 in 1995 [1]. SHA-2 is the successor to SHA-1 and is a family of 4 hash functions, with the most complex being SHA-512, so-called because it produces an output 512 bits in length [1].

SHA-512 is an example of a cryptographic hash function. That is, a function which can read in a message and compute a fixed-length string (or _digest_) which can be seen as a unique representation of that message, much like a fingerprint [2]. The motivation for hash functions like SHA-512 over digital signature schemes like RSA, lies in their ability to produce a short, fixed-length digest for messages of arbitrary length. In other words, even if we had a message that is hundreds of megabytes in size, it should still be relatively fast to compute its digest. This is in contrast to algorithms like RSA where the length of the plaintext is limited [2].

An important characteristic of hash functions like SHA-512 is they are highly sensitive to all input bits [2]. This means that even minor alterations to the message will result in a vastly different digest being produced. This is called the avalanche effect [3]. For example, below the input "abc" produces a SHA-256 output that is markedly distinct from the string "abb", despite only a single letter being modified.

<div align="center">
  <img src="https://user-images.githubusercontent.com/37158241/111521283-decc5a80-8750-11eb-91ed-b04bcbced56f.png" />
</div>

As a result of this property, hash functions like SHA-512 have found important application in the creation of digital signatures and in verifying the integrity of messages, e.g. by providing a way to ensure digital files have not been modified [1]. Just some of the many other real-world use cases of hash functions include the Git revision control system, which uses them to identify files being tracked in a repository [1]. Meanwhile SHA-512's sibling algorithm, SHA-256, is used in popular authentication and encryption protocols, including SSL, TLS, IPsec, SSH, and PGP [4]. In Linux systems, SHA-256 is also used for hashing passwords, while cryptocurrencies like Bitcoin use it for verifying transactions [4].

## Q & A

### _Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?_

One of the main distinctions between hashing and encryption is reversibility. Encryption algorithms often require both an input as well as a key in order to generate the output (or ciphertext). This process is reversible as anyone able to obtain the key will also be able to decrypt the ciphertext and therein view the original message [5]. In contrast, SHA-512, like all algorithms specified in NIST FIPS 180-4 are "one-way hash functions" [6]. It is therefore not required for the specific hash algorithm used to be kept secret because the digest cannot be converted back to its original form [5]. However, while it is not technically possible to reverse a hash in order to retrieve the original message, hash algorithms like SHA-512 are still susceptible to collisions - where two messages produce the same hash.

A central characteristic of any secure hash function like SHA-512 is that of "preimage resistance", also referred to as "one-wayness". This means that for any given hash, it must be computationally infeasible to find a message that will produce the same hash output [2]. Meanwhile, a second property of hash functions is that of "second preimage resistance", also referred to as (weak) collision resistance. This means that for hash algorithms like SHA-512, it should be infeasible to create two distinct plaintext messages that produce the exact same digest [2]. These are crucial characteristics of hash algorithms as they are widely used for verifying digital files and deriving cryptographic keys. If a bad actor were able to feasibly construct a message that produces the same hash output, they could perform substitution attacks, replacing a file with another malicious file that produces the same digest [2].

It is not possible to design a hash function that is fully resistant to collisions. This is because the input to a hash function is theoretically infinite, while the digest will always be the same length. For this reason, it must be true that multiple inputs will inevitably produce the same hash value [2]. This is illustrated by the _Pigeonhole Principle_, which states that if a pigeon loop were to contain 100 birds but only 99 holes, at least one hole must be occupied by two birds [2]. Because every hash algorithm produces an output with a fixed number of bits (**_n_**), there are 2<sup>_n_</sup> possible digests that can be computed by that algorithm, while there is an infinite number of possible inputs [2] (in the case of SHA-512 there are 2<sup>512</sup> possible outputs). In other words, there are an infinite number of possible inputs that can produce the same output. Because of this, even given unlimited computing power it is not possible to retrieve the _exact_ message that produced a given hash value as there are so many inputs that could produce the same hash [1]. It would of course be possible to determine _some_ possible messages that produce that hash (i.e. collisions), given enough time and resources, but it would not be possible to determine precisely what input was fed to the algorithm originally [1].

### _Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?_

As mentioned previously, secure hash algorithms should be "preimage resistant". A preimage of a given hash value (**_H_**), is any message (**_M_**) that when run through the hash algorithm will produce the value of **_H_** [1]. In other words, a preimage is any message wherein `Hash(M) == H` [1]. Preimages are distinct from collisions, which is where two distinct input messages produce the same hash.

If given a hash value, one can search for preimages using a brute force technique which involves continuously checking the hash output of different messages until eventually finding a message that produces the same output as the target hash. The below C code is adapted from the pseudo-code shown on page 174 of [1]. Here, the `find_preimage()` function takes a SHA-512 hash (called `target`) and will iteratively try to find the SHA-512 hash of a random plaintext message (`m`). It will then use `strcmp()` to check if the hash of that message (`hash_m`) equals the hash value passed into the function. If so, the function will return the matching input message (`m`), or otherwise continue looping until a match is found.

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

In the code below, the `for` loop (in which the `find_preimage()` function is called), executes once for each SHA-512 string in the `targets[]` array. On each iteration, once a preimage is found, the result is subsequently printed to the screen.

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

However, this sort of brute force attack wherein we try as many possible inputs in order to find a message corresponding to a given digest would require 2<sup>_L_</sup> evaluations, where **_L_** is the length of the digest (for SHA-512 that is 512 bits) [6]. Such a technique can therefore be considered wildly impractical due to the length of time it would take to successfully find even just a single an input message, as explained in [7]. (Although one should note that that particular example involved _collision attacks_ on SHA-256; preimage attacks on SHA-512 would take a considerably longer amount of time.)

### _How difficult is it to find a hash digest beginning with at least twelve zeros?_

The occurance of leading zeros in hash digests has particular significance in the area of mining cryptocurrencies, like Bitcoin.

In Bitcoin mining, individuals called "miners" compete to find a new block in the blockchain. Each block contains a header, which in turn contains a target hash. The objective of the mining process is to add a random value (called a "nonce") to the header of the current block and then calculate its SHA-256 hash [8]. The process is repeated using a brute-force technique wherein the value of the nonce is continuously altered until eventually the hash digest produced is smaller than the value of the target hash for that block [8,9].

Because in the Bitcoin blockchain it is a requirement that each block take about 10 minutes to be mined [9], in order to ensure this remains constant the so-called difficulty level is periodically adjusted by either increasing or decreasing the number of leading zeros in the target hash of a given block [9]. The entire mining process is significantly difficult due to both the length of time and the amount of processing power required, an issue that becomes more apparant as more leading zeros are present in the target hash.

In [10] the author uses a Python script in order to demonstrate how the time to generate an acceptable hash rapidly increases as more leading zeros are added to the target hash. Using just a laptop, generating a hash with 7 leading zeros took about 16 minutes and 675 million iterations. At the time that article was written, the Bitcoin difficulty level required 19 leading zeros, with miners collectively calculating 117 Exahashes per second (one Exahash is 1,000,000,000,000,000,000) [10]. Today Bitcoin miners are collectively calculating at a rate of over 163 Exahashes per second (see below) [11].

![hash-rate](https://user-images.githubusercontent.com/37158241/112484796-2a46c000-8d72-11eb-8293-b56d9af5acba.png)

When [12] was written in 2014, a successful hash would have needed to start with 17 zeros, meaning just one out of 1.4x10<sup>20</sup> hashes would be successful. Finding such a hash would be more difficult than finding a particular grain of sand out of all the grains of sand on Earth [12]. Today, at the time of writing it is even harder as the latest Bitcoin block had a target hash consisting of 20 leading zeros and a difficulty level of about 21.866 trillion [13].

```
00000000000000000000edfc2d32a0d6302c200b34d195afa1588d4f61789e5a
```

Although as mentioned previously it takes an average of 10 minutes for one of the miners in the network to discover a block, calculating a hash like the one above requires significant computataional power and miners therefore generally require specialised hardware in order to be successful [10].

## References

1. Jean-Philippe Aumasson. _Serious cryptography: a practical introduction to modern encryption_. Chapter 6 – Hash Functions. No Starch Press, 2017. ISBN: 978-1-59327-826-7.

2. Christof Paar and Jan Pelzl. _Understanding cryptography: a textbook for students and practitioners_. Chapter 11 – Hash Functions. Springer Science & Business Media, 2009, ISBN: 978-3-642-04101-3. DOI: [10.1007/978-3-642-04101-3](https://doi.org/10.1007/978-3-642-04101-3).

3. [_Secure Hash Algorithms_](https://brilliant.org/wiki/secure-hashing-algorithms/). Brilliant.

4. [_SHA-256 Algorithm Overview_](https://www.solarwindsmsp.com/blog/sha-256-encryption). SolarWinds MSP. 12 Sep, 2019.

5. [_Hashing explained: Why it's your best bet to protect stored passwords_](https://www.csoonline.com/article/3602698/hashing-explained-why-its-your-best-bet-to-protect-stored-passwords.html). CSO Online. Lucian Constantin. Jan 13, 2021.

6. Quynh H. Dang. _Secure Hash Standard_. Federal Inf. Process. Stds. (NIST FIPS) - 180-4. Gaithersburg, MD: US Department of Commerce, National Institute of Standards and Technology, Aug. 2015. DOI: [10.6028/NIST.FIPS.180-4](https://doi.org/10.6028/NIST.FIPS.180-4).

7. [_Why haven't any SHA-256 collisions been found yet?_](https://crypto.stackexchange.com/a/47810). user47922. StackExchange Cryptography. May 29 2017.

8. [_How Bitcoin mining really works_](https://www.freecodecamp.org/news/how-bitcoin-mining-really-works-38563ec38c87/). Subhan Nadeem. freeCodeCamp. May 31, 2018.

9. [_Introduction to Blockchain_](https://medium.com/@zaid960928/introduction-to-blockchain-ad0ab0628c15). Zaid Khaishagi. Jun 16, 2018.

10. [_Bitcoin Proof of Work_](https://creativedata.stream/bitcoin-proof-of-work/). Bob Peers. May 11, 2020.

11. [_Total Hash Rate (TH/s)_](https://www.blockchain.com/charts/hash-rate). Accessed 25/03/2021. Blockchain<span></span>.com.

12. [_Mining Bitcoin with pencil and paper: 0.67 hashes per day_](http://www.righto.com/2014/09/mining-bitcoin-with-pencil-and-paper.html). Ken Shirriff's blog. Ken Shirriff. Sep, 2014.

13. [_Block 676248_](https://www.blockchain.com/btc/block/00000000000000000000edfc2d32a0d6302c200b34d195afa1588d4f61789e5a). Blockchain<span></span>.com.
