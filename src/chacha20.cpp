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

#include "chacha20.hpp"
#include "chacha20_common.h"
#include <random>

void chacha20::set_nonce(void *nonce){
    _state[13] = ((uint32_t*)nonce)[0];
    _state[14] = ((uint32_t*)nonce)[1];
    _state[15] = ((uint32_t*)nonce)[2];
    lendian32(_state[13]);
    lendian32(_state[14]);
    lendian32(_state[15]);
}
chacha20::chacha20(){
    _state[0] = 0x61707865;
    _state[1] = 0x3320646e;
    _state[2] = 0x79622d32;
    _state[3] = 0x6b206574;
    std::random_device rd; // non deterministic random source
    for(int i=4; i<16; ++i) _state[i] = rd();
    _state[12] = 0;
}
chacha20::chacha20(void *key, void* nonce, uint32_t counter)
{
    _state[0] = 0x61707865;
    _state[1] = 0x3320646e;
    _state[2] = 0x79622d32;
    _state[3] = 0x6b206574;
    for (int i = 0; i < 8; i++){
        _state[4+i] = ((uint32_t*)key)[i];
        lendian32(_state[4+1]);
    }
    _state[12] = counter;
    set_nonce(nonce);
}
uint32_t chacha20::counter() const{
    return _state[12];
}
void chacha20::counter(uint32_t c){
    _state[12] = c;
}

void chacha20::operator()(void *block){
    uint32_t *w = (uint32_t*)block; // working buffer
    for (int i = 0; i < 16; i++)
        w[i] = _state[i];      
    for (int i = 0; i < 10; i++)
        inner_block(w);
    for (int i = 0; i < 16; i++)
    {
        w[i] += _state[i];  
        lendian32(w[i]);  
    }
    _state[12]++;
}
void chacha20::operator()(void* block, uint32_t counter){
    _state[12] = counter;
    this->operator()(block);
}
void chacha20::encrypt(const void* data, uintmax_t len, void* out){
    uint8_t stream[chacha20::blockSize()];
    int r = len & 63;
    uintmax_t n = len - r;
    // encrypt whole blocks
    for (uintmax_t i = 0; i < n; i+=chacha20::blockSize())
    {
        this->operator()(stream);
        for (int j = 0; j < chacha20::blockSize(); j++)
            ((uint8_t*)out)[i+j] = ((uint8_t*)data)[i+j] ^ stream[j];        
    }
    // take care of the remaining bytes, if any
    if(r){
        this->operator()(stream);
        for (int i = 0; i < r; i++)
            ((uint8_t*)out)[i+n] = ((uint8_t*)data)[i+n] ^ stream[i];
    }
}
