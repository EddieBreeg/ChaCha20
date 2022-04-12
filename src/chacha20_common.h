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


// This file contains common definitions for both the C and C++ version


// Converts x to little-endian order
#define lendian32(x){\
    uint8_t b[4] = {                \
        (uint8_t)(x&0xff),          \
        (uint8_t)((x>>8)&0xff),     \
        (uint8_t)((x>>16)&0xff),    \
        (uint8_t)((x>>24)&0xff),    \
    };                              \
    x = *(uint32_t*)b;              \
}

// Rotates a 32-bit integer n steps to the left
#define ROL32(x, n)     (((x) << (n)) | ((x) >> (32 - (n))))

// ChaCha20 Quarter-Rount mix function
#define QR(a, b, c, d){                             \
    (a) += (b); (d) ^= (a); (d) = ROL32(d, 16);     \
    (c) += (d); (b) ^= (c); (b) = ROL32(b, 12);     \
    (a) += (b); (d) ^= (a); (d) = ROL32(d, 8);      \
    (c) += (d); (b) ^= (c); (b) = ROL32(b, 7);      \
}

// ChaCha20 inner-block function
// performs two complete rounds on the internal state
#define inner_block(s){\
    QR(s[0],    s[4],   s[8],  s[12]); \
    QR(s[1],    s[5],   s[9],  s[13]); \
    QR(s[2],    s[6],  s[10],  s[14]); \
    QR(s[3],    s[7],  s[11],  s[15]); \
    QR(s[0],    s[5],  s[10],  s[15]); \
    QR(s[1],    s[6],  s[11],  s[12]); \
    QR(s[2],    s[7],   s[8],  s[13]); \
    QR(s[3],    s[4],   s[9],  s[14]); \
}


#ifdef __cplusplus
}
#endif