#pragma once

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


#ifdef __cplusplus
extern "C"{
#endif

#include <inttypes.h>
#define CHACHA20_BLOCKSIZE  64

// opaque struct representing the internal state
// for ChaCha20
typedef struct chacha20_state chacha20_state;

// inits the ChaCha20 state from a key, a nonce and an inital counter
chacha20_state* chacha20_init(const void* key, const void* nonce, uint32_t counter);

// generates the next block in the pseudo-random keystream
// and stores the result in the ouput block
void chacha20_block(chacha20_state *state, void* block);

// utility function to encrypt the input data
// stores the result in the output buffer
void chacha20_encrypt(chacha20_state* state, const void* data, uintmax_t len, void *output);

void chacha20_set_key(chacha20_state* chacha, const void *key);
void chacha20_set_nonce(chacha20_state *chacha, const void* nonce);
void chacha20_set_counter(chacha20_state* state, uint32_t c);
uint32_t chacha20_get_counter(chacha20_state* state);

// resource cleaning
void chacha20_clean(chacha20_state* state);

#ifdef __cplusplus
}
#endif