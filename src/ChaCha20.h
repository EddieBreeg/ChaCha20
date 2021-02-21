#ifndef CHACHA20_H
#define CHACHA20_H

#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 32
#define NONCE_SIZE 12
#define uint32 unsigned int
#define byte unsigned char
#define R(x, n) (x<<n | x>>(32-n))
#define LITTLE_ENDIAN(b) b[0] | (b[1]<<8) | (b[2]<<16) | (b[3]<<24)

void quarterRound(uint32* a, uint32* b, uint32* c, uint32* d);
void inner_block(uint32 state[]);
void chacha20_block(byte* key, uint32 counter, byte* nonce, byte* output);

#endif