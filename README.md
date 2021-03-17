# Theory of Algorithms Project

Y4S2 Theory of Algorithms Project

## Description

A C program that calculates & outputs the SHA-512 digest of a given input file.

## Compilation

You can compile and run the program as follows:

```sh
$ make
$ ./sha512 [options]
```

### Options

| Option              | Description             |
| ------------------- | ----------------------- |
| `-h, --help`        | Prints some help text.  |
| `-f, --file <file>` | Path to the input file. |

### Testing

```sh
$ make test
```

## What is SHA-512 & Why is it Important?

SHA-512 is an example of a cryptographic hash function. That is, a function which can read in a message and compute a fixed-length string (or _digest_) which can be referred to as a unique representation of that message [1]. The motivation for hash functions like SHA-512 over digital signature schemes like RSA, lies in their ability to produce a short, fixed-length digest for messages of arbitrary length. In other words, even if we wanted to hash a message that is hundreds of megabytes in size, it would still be relatively fast to compute the message's digest.

An important characteristic of hash functions is they are highly sensitive to all input bits [1]. This means that even minor alterations to the message will result in a vastly different digest being produced. As a result, hash functions like SHA-512 have important application in digital signatures and verifying the integrity of messages, to ensure digital files have not been modified [2]. Just some of the real-world use cases of hash functions include the Git revision control system, which uses them to identify files being tracked in a repository [2], as well crypto-currencies like Bitcoin.

## Q & A

**_Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?_**

**_Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?_**

**_How difficult is it to find a hash digest beginning with at least twelve zeros?_**

## References

[1] - Christof Paar and Jan Pelzl. _Understanding cryptography: a textbook for students and practitioners_. Chapter 11 - Hash Functions. Springer Science & Business Media, 2009, ISBN: 978-3-642-04101-3. DOI: [10.1007/978-3-642-04101-3](https://doi.org/10.1007/978-3-642-04101-3).

[2] - Jean-Philippe Aumasson. _Serious cryptography: a practical introduction to modern encryption_. Chapter 6 – Hash Functions. No Starch Press, 2017. ISBN: 978-1-59327-826-7.

[3] - Quynh H. Dang. _Secure Hash Standard_. Federal Inf. Process. Stds. (NIST FIPS) - 180-4. Gaithersburg, MD: US Department of Commerce, National Institute of Standards and Technology, Aug. 2015. DOI: [10.6028/NIST.FIPS.180-4](https://doi.org/10.6028/NIST.FIPS.180-4).
