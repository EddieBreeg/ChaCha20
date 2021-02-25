#include "ChaCha20.h"

void quarterRound(uint32* a, uint32* b, uint32* c, uint32* d)
{
    *a += *b; *d ^= *a; *d = R(*d, 16);
    *c += *d; *b ^= *c; *b = R(*b, 12);
    *a += *b; *d ^= *a; *d = R(*d, 8);
    *c += *d; *b ^= *c; *b = R(*b, 7);
}
void inner_block(uint32 state[])
{
    quarterRound(state,   state+4, state+8,  state+12);
    quarterRound(state+1, state+5, state+9,  state+13);
    quarterRound(state+2, state+6, state+10, state+14);
    quarterRound(state+3, state+7, state+11, state+15);
    quarterRound(state,   state+5, state+10, state+15);
    quarterRound(state+1, state+6, state+11, state+12);
    quarterRound(state+2, state+7, state+8,  state+13);
    quarterRound(state+3, state+4, state+9,  state+14);
}
// Sets up the state matrix from the key, nonce and block counter, hashes it and copies the 64-byte result into the output buffer.
void chacha20_block(byte* key, uint32 counter, byte* nonce, byte* output)
{
    // setting up the initial state
    uint32 state[] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
        0,0,0,0,
        0,0,0,0,
        counter,0,0,0
    };
    for(int i=0;i<8;i++)
        state[i+4] = LITTLE_ENDIAN((key+4*i));
    for(int i=0;i<3;i++)
        state[i+13] = LITTLE_ENDIAN((nonce+4*i));
    // creating the working state
    uint32 workingState[16]; memcpy(workingState, state, 16*sizeof(uint32));
    // performs 20 rounds on the working state
    for(int i=0; i<10; i++)
        inner_block(workingState);
    // adds the result to the initial state
    for(int i=0; i<16; i++)
        state[i]+=workingState[i];

    for (int i = 0; i < 16; i++)
    {
        byte* d = output + 4*i;
        for (int j = 0; j < 4; j++)
        {
            d[j] = state[i] & 0xff;
            state[i] >>= 8;
        }
    }
}
// Encrypts the n-byte input buffer by XORing it with the ChaCha20 keystream. If n>64, the function will only encrypt 64 bytes
void chacha20_cipher(byte key[KEY_SIZE], uint32 counter, byte nonce[NONCE_SIZE], byte input[STATE_BUFFER_SIZE], uint32 n)
{
    byte stream[STATE_BUFFER_SIZE];
    chacha20_block(key, counter, nonce, stream);
    for(size_t i=0; i < (n<STATE_BUFFER_SIZE? n:STATE_BUFFER_SIZE); i++)
        input[i] ^= stream[i];
}