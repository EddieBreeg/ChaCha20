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

#include <inttypes.h>

#define CHACHA20_BLOCKSIZE  64

// opaque struct representing the internal state
// for ChaCha20
class chacha20
{
private:
    uint32_t _state[CHACHA20_BLOCKSIZE];
public:
    // default constructor -> should only be used when using chacha20 as a CPRNG
    chacha20();
    // constructs the ChaCha20 state from a key, a nonce and an inital counter
    chacha20(void *key, void *nonce, uint32_t counter = 0);
    chacha20(const chacha20&) = delete;
    void set_nonce(void *nonce);
    // utility method to encrypt the input data
    // stores the result in the output buffer
    void encrypt(const void* data, uintmax_t len, void* out);
    // generates the next block in the pseudo-random keystream
    // and stores the result in the ouput block
    void operator()(void *block);
    // generates a block at the given position in the keystream
    void operator()(void *block, uint32_t counter);
    // getter/setter for the internal counter
    uint32_t counter() const;
    void counter(uint32_t c);
    static inline constexpr unsigned blockSize() { return CHACHA20_BLOCKSIZE; };
};

