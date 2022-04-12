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
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



uint32_t xorshift32(uint32_t x){
    x ^= x << 13;
	x ^= x >> 17;
	return x ^ (x << 5);
}
struct size{
    float val; const char* suffix;
};
struct size makeSizeSuffix(uintmax_t n){
    struct size res = {.0f, "KiB"};
    int k = n>>30? 30:
        n>>20? 20:10;
    res.val = (float)n / (float)(1<<k);
    switch (k)
    {
    case 30: res.suffix = "GiB"; break;
    case 20: res.suffix = "MiB"; break;
    }
    return res;
}
/*
    ===========================================================
    This speedtest generates ChaCha20 keystream blocks for
    n seconds, then measures the total amount of generated data
    as well as the average bitrate
    ===========================================================
*/

int main(int argc, char const *argv[])
{
    uint32_t lfsr = time(NULL) ^ 0x5c5c5c5c;
    uint32_t nonce[3] = {
        lfsr = xorshift32(lfsr),
        lfsr = xorshift32(lfsr),
        lfsr = xorshift32(lfsr)
    };
    printf("Nonce: ");
    for (int i = 0; i < 12; i++)
        printf("%02x", ((uint8_t*)nonce)[i]);
    printf("\n");

    uint64_t key[] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31
    };
    chacha20 s(key, nonce);
    uint8_t block[chacha20::blockSize];
    time_t start = time(NULL);
    size_t n;
    time_t duration = argc<2? 3:atoi(argv[1]);
    printf("Starting for %lus\n", duration);
    for (n=0; (time(NULL)-start) < duration; n+=chacha20::blockSize)
        s(block);
    struct size S = makeSizeSuffix(n);
    printf("Generated %lu bytes (%f %s) in %lus\n", n, S.val,S.suffix, duration);
    S = makeSizeSuffix(n / duration);
    printf("Average: %f %s/s\n", S.val, S.suffix);
    return 0;
}
