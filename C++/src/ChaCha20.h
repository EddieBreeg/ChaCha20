#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>

#define KEY_SIZE 32
#define NONCE_SIZE 12
#define STATE_BUFFER_SIZE 64
#define R(x, n) (x<<n | x>>(32-n))
#define LITTLE_ENDIAN(b) b[0] | (b[1]<<8) | (b[2]<<16) | (b[3]<<24)

typedef unsigned int uint32;
typedef unsigned char byte;

class ChaCha20
{
public:
    // The index of the block to generate in the key-stream
    uint32 blockCounter;
    // Inits the ChaCha20 object from the key, the nonce and the initial block counter
    ChaCha20(byte* key, byte* nonce, uint32 blockCounter = 0);
    // Hashes the internal state buffer
    void block(void);
    // Hashes the internal state buffer using the provided block counter
    void block(uint32 blockCounter);
    // Hashes the internal state, performs the XOR with the n-byte data array and increments blockCounter
    void chacha20_cipher(byte data[], uint32 n);
    // Returns _output[i]
    const uint32 operator[](int i);
    // print the output buffer to the console
    friend std::ostream& operator<<(std::ostream& s, const ChaCha20& chacha20);
    // Destroys the ChaCha20 object
    ~ChaCha20();
private:
    // The initial state matrix
    uint32* _initState;
    // The output of the block function
    byte* _output;
};
