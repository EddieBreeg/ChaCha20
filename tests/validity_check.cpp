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
#include <stdio.h>
#include "chacha20.h"

#define ESC "\033["
#define STYLE_ERROR         ESC "31;1m"
#define STYLE_DEFAULT       ESC "0m"
#define STYLE_GOOD          ESC "32;1m"


int check(const uint8_t *expected, const uint8_t* actual, size_t len){
    for (int i = 0; i < len; i++)
        if(actual[i] != expected[i]) return i;
    return 0;
}

int main(int argc, char const *argv[])
{
    // ===============
    // ==== SETUP ====
    // ===============
    uint8_t key[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };
    uint8_t nonce[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00
    };
    const int len = 114;
    chacha20 chacha(key, nonce, 1);
    chacha20_state* c_chacha = chacha20_init(key, nonce, 1);
    
    uint8_t cipherText[len];
    const char msg[] = "Ladies and Gentlemen of the class of '99: "
    "If I could offer you only one tip for the future, sunscreen would be it.";
    const uint8_t *expected = (const uint8_t*)
    "\x6e\x2e\x35\x9a\x25\x68\xf9\x80\x41\xba\x07\x28\xdd\x0d\x69\x81"
    "\xe9\x7e\x7a\xec\x1d\x43\x60\xc2\x0a\x27\xaf\xcc\xfd\x9f\xae\x0b"
    "\xf9\x1b\x65\xc5\x52\x47\x33\xab\x8f\x59\x3d\xab\xcd\x62\xb3\x57"
    "\x16\x39\xd6\x24\xe6\x51\x52\xab\x8f\x53\x0c\x35\x9f\x08\x61\xd8"
    "\x07\xca\x0d\xbf\x50\x0d\x6a\x61\x56\xa3\x8e\x08\x8a\x22\xb6\x5e"
    "\x52\xbc\x51\x4d\x16\xcc\xf8\x06\x81\x8c\xe9\x1a\xb7\x79\x37\x36"
    "\x5a\xf9\x0b\xbf\x74\xa3\x5b\xe6\xb4\x0b\x8e\xed\xf2\x78\x5e\x42"
    "\x87\x4d";
    int i;
    // =================
    // ==== C TEST =====
    // =================
    C_TEST: chacha20_encrypt(c_chacha, msg, len, cipherText);
    if (i = check(expected, cipherText, len))
        printf("[C TEST]\t" STYLE_ERROR "Error at index %i: expected 0x%02X, got 0x%02X\n"
            STYLE_DEFAULT,
            i, expected[i], cipherText[i]);
    else printf("[C TEST]\t" STYLE_GOOD " Passed\n" STYLE_DEFAULT);
    // ==================
    // ==== C++ test ====
    // ==================
    chacha.encrypt(msg, len, cipherText);
    if (i = check(expected, cipherText, len))
        printf("[C++ TEST]\t" STYLE_ERROR "Error at index %i: expected 0x%02X, got 0x%02X\n"
            STYLE_DEFAULT,
            i, expected[i], cipherText[i]);
    else printf("[C++ TEST]\t" STYLE_GOOD " Passed\n" STYLE_DEFAULT);
    chacha20_clean(c_chacha);
    return 0;
}
