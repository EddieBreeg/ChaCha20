/*
MIT License

Copyright (c) 2021 EddieBreeg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "chacha20.h"
#include "chacha20_common.h"
#include <stdlib.h>

typedef struct chacha20_state
{
    uint32_t s[16]; // the state buffer
} chacha20_state;

chacha20_state* chacha20_init(const void* key, const void* nonce, uint32_t counter){
    chacha20_state *state = malloc(sizeof(*state));
    if(!state) return NULL;
    state->s[0] = 0x61707865;
    state->s[1] = 0x3320646e;
    state->s[2] = 0x79622d32;
    state->s[3] = 0x6b206574;
    chacha20_set_key(state, key);
    chacha20_set_nonce(state, nonce);
    state->s[12] = counter;
    return state;
}
void chacha20_set_key(chacha20_state* chacha, const void *key){
    for (int i = 0; i < 32; i++)
        ((uint8_t*)chacha->s)[16+i] = ((uint8_t*)key)[i];
}
void chacha20_set_nonce(chacha20_state *chacha, const void* nonce){
    for (int i = 0; i < 12; i++)
        ((uint8_t*)chacha->s)[52+i] = ((uint8_t*)nonce)[i];
}
void chacha20_block(chacha20_state *s, void* block){
    uint32_t *w = (uint32_t*)block;
    for (size_t i = 0; i < 16; i++)
        w[i] = s->s[i];      
    for (size_t i = 0; i < 10; i++)
        inner_block(w);
    for (size_t i = 0; i < 16; i++)
    {
        w[i] += s->s[i];
        lendian32(w[i]);
    }
    s->s[12]++;
}
void chacha20_encrypt(chacha20_state* s, const void* data, uintmax_t len, void* out){
    uint8_t stream[CHACHA20_BLOCKSIZE];
    int r = len & 63;
    uintmax_t n = len - r;
    for (uintmax_t i = 0; i < n; i+=CHACHA20_BLOCKSIZE)
    {
        chacha20_block(s, stream);
        for (int j = 0; j < CHACHA20_BLOCKSIZE; j++)
            ((uint8_t*)out)[i+j] = ((uint8_t*)data)[i+j] ^ stream[j];        
    }
    if(r){
        chacha20_block(s, stream);
        for (int i = 0; i < r; i++)
            ((uint8_t*)out)[i+n] = ((uint8_t*)data)[i+n] ^ stream[i];
    }
}
void chacha20_set_counter(chacha20_state* state, uint32_t c){
    state->s[12] = c;
}
uint32_t chacha20_get_counter(chacha20_state* state){
    return state->s[12];
}
void chacha20_clean(chacha20_state* s){
    free(s);
}