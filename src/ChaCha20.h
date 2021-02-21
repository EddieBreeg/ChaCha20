#ifndef CHACHA20_H
#define CHACHA20_H

#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 32
#define NONCE_SIZE 12
#define STATE_BUFFER_SIZE 64
#define R(x, n) (x<<n | x>>(32-n))
#define LITTLE_ENDIAN(b) b[0] | (b[1]<<8) | (b[2]<<16) | (b[3]<<24)

typedef unsigned int uint32;
typedef unsigned char byte;

void chacha20_block(byte* key, uint32 counter, byte* nonce, byte* output);
void chacha20_cipher(byte key[KEY_SIZE], uint32 counter, byte nonce[NONCE_SIZE], byte input[STATE_BUFFER_SIZE], uint32 n);

#endif