# ChaCha20 C
A C implementation of the ChaCha20 encryption scheme


##  Macros and types

- `KEY_SIZE`: The ChaCha20 key size, in bytes := 32
- `NONCE_SIZE`: The ChaCha20 nonce size in bytes := 12
- `STATE_BUFFER_SIZE`: The ChaCha20 state buffer size in bytes := 64
- `uint32`: Represents a 32-bit unsigned integer
- `byte`: represents an 8-bit unsigned integer
- `R(x, n)`: The rotation of x (`uint32`) by n bits to the left
- `LITTLE_ENDIAN(b)`: The conversion of b (`byte[4]`) to a little endian `uint32` integer

## Functions

```C
void chacha20_block(byte* key, uint32 counter, byte* nonce, byte* output)
```
Sets up the state matrix from the key, nonce and block counter, hashes it and copies the 64-byte result into the output buffer.

```C
void chacha20_cipher(byte key[KEY_SIZE], uint32 counter, byte nonce[NONCE_SIZE], 
    byte input[STATE_BUFFER_SIZE], uint32 n)
```
Encrypts the n-byte input buffer by XORing it with the ChaCha20 keystream.

## Example
This code takes a file path as an argument, and encrypts it using a test key and a test nonce.\
[test2.c](tests/test2.c)
```C
#include <stdio.h>
#include "../src/ChaCha20.h"

// reads and encrypts the file which name is argv[1]
int main(int argc, char const *argv[])
{

    FILE* input = fopen(argv[1], "rb");
    if(!input) exit(1);

    FILE* outFile = fopen(argv[2], "wb");
    if(!outFile) outFile = fopen("result.out", "wb");

    byte key[KEY_SIZE];
    for (int i = 0; i < 32; i++)
        key[i] = i;
    byte nonce[NONCE_SIZE] = {0x79, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x74};
    uint32 counter = 0;
    byte buffer[STATE_BUFFER_SIZE];
    size_t n;
    do
    {
        n = fread(buffer, 1, STATE_BUFFER_SIZE, input);
        chacha20_cipher(key, counter++, nonce, buffer, n);
        fwrite(buffer, 1, n, outFile);
    } while (n);
    

    return 0;
}
```