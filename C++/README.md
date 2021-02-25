# CharChar20 C++

A C++ implementation of the ChaCha20 encryption scheme.

##  Macros and types

- `KEY_SIZE`: The ChaCha20 key size, in bytes := 32
- `NONCE_SIZE`: The ChaCha20 nonce size in bytes := 12
- `STATE_BUFFER_SIZE`: The ChaCha20 state buffer size in bytes := 64
- `uint32`: Represents a 32-bit unsigned integer
- `byte`: represents an 8-bit unsigned integer
- `R(x, n)`: The rotation of x (`uint32`) by n bits to the left
- `LITTLE_ENDIAN(b)`: The conversion of b (`byte[4]`) to a little endian `uint32` integer
- `class ChaCha20`

## The ChaCha20 class

### Public members

```C++
uint32 blockCounter
```
Represents the position in the pseudo-random key-stream.
```C++
ChaCha20(byte* key, byte* nonce, uint32 blockCounter = 0)
```
Builds an instance of the ChaCha20 class from a 32-byte key, a 12-byte nonce and (optionally) an initial block counter.
```C++
void block(uint32 blockCounter)
void block(void)
```
Hashes the internal state of the object. The result is a 64-byte buffer. If a counter is provided, it will override the blockCounter member.
```C++
void chacha20_cipher(byte data[], uint32 n)
```
First hashes the internal state, then performs a XOR between the generated block and the n-byte data buffer, and finally increments the blockCounter value.
```C++
const uint32 operator[](int i)
```
Returns the i_th byte of the _output buffer (see below)
```C++
~ChaCha20()
```
Destroys the ChaCha20 instance.

### Private members

```C++
uint32* _initState
```
Represents the state matrix at the beginning of the hash operation.
```C++
byte* _output
```
Contains the output of the block function.

## Example

This is an example code that encrypts a file passed as an argument, using a key read from the file passed as another argument (see the cpp file [here](tests/test2.cpp)):
```C++
#include "../src/ChaCha20.h"
#include <stdio.h>

#define OUT_FILE argc<4? "output.out": argv[3]

int main(int argc, char const *argv[])
{
    FILE* keyFile = fopen(argv[2], "rb");
    if(!keyFile)
    {
        printf("%s: key file not found.", argv[2]);
        exit(EXIT_FAILURE);
    }
    byte key[KEY_SIZE];
    fread(key, sizeof(byte), KEY_SIZE, keyFile);
    byte nonce[NONCE_SIZE] = {0,0,0,0,0,0,0,0x4a,0,0,0,0};
    
    FILE* dataFile = fopen(argv[1], "rb");
    FILE* out = fopen(OUT_FILE, "wb");
    if(!dataFile)
    {
        printf("Failed to open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    else if(!out)
    {
        printf("Failed to open %s\n", OUT_FILE);
    }
    byte buffer[STATE_BUFFER_SIZE];
    uint32 n;
    ChaCha20 chacha20(key, nonce, 1);
    do
    {
        n = fread(buffer, sizeof(byte), STATE_BUFFER_SIZE, dataFile);
        chacha20.chacha20_cipher(buffer, n);
        fwrite(buffer, sizeof(byte), n, out);
    } while (n);
    
    fclose(keyFile);
    fclose(dataFile);
    fclose(out);
    return 0;
}
```

## Validity of the implementation

Both [test.c](../C/tests/test.c) and [test.cpp](tests/test.cpp) are here to check the validity of this implementation, according to the [RFC 7539](https://tools.ietf.org/html/rfc7539).\
These two programs run the ChaCha20 algorithm using the same parameters as used in the example section [2.4.2](https://tools.ietf.org/html/rfc7539#section-2.4.2) of said RFC:
- key=00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14:15:16:17:18:19:1a:1b:1c:1d:1e:1f
- nonce=(00:00:00:00:00:00:00:4a:00:00:00:00)
- initial counter=1
- message="Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it."

The expected cipher text is:\
6e 2e 35 9a 25 68 f9 80 41 ba 07 28 dd 0d 69 81 e9 7e 7a ec 1d 43 60 c2 0a 27 af cc fd 9f ae 0b f9 1b 65 c5 52 47 33 ab 8f 59 3d ab cd 62 b3 57 16 39 d6 24 e6 51 52 ab 8f 53 0c 35 9f 08 61 d8 07 ca 0d bf 50 0d 6a 61 56 a3 8e 08 8a 22 b6 5e 52 bc 51 4d 16 cc f8 06 81 8c e9 1a b7 79 37 36 5a f9 0b bf 74 a3 5b e6 b4 0b 8e ed f2 78 5e 42 87 4d