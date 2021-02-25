#pragma once

#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 32
#define NONCE_SIZE 12
#define STATE_BUFFER_SIZE 64
#define R(x, n) (x<<n | x>>(32-n))
#define LITTLE_ENDIAN(b) b[0] | (b[1]<<8) | (b[2]<<16) | (b[3]<<24)

typedef unsigned int uint32;
typedef unsigned char byte;

class ChaCha20
{
private:
    uint32* _initState;
    byte* _output;
public:
    uint32 blockCounter;
    ChaCha20(byte* key, byte* nonce, uint32 blockCounter = 0);
    const uint32 operator[](int i);
    void block(void);
    void block(uint32 blockCounter);
    void chacha20_cipher(byte data[], uint32 n);
    ~ChaCha20();
};
