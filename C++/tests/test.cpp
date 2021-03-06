#include "../src/ChaCha20.h"
#include <iostream>

#define XCHARS "0123456789abcdef"
#define HEX(b) XCHARS[(b>>4) & 15] << XCHARS[b & 15]

/* This code performs the example provided in section 2.4.2 of the RFC 7539.
* For full detail about this example follow this link: 
* https://tools.ietf.org/html/rfc7539#section-2.4.2 */
int main(int argc, char const *argv[])
{
    byte key[32];
    for (size_t i = 0; i < 32; i++)
        key[i] = i;
    
    byte nonce[12] = {0,0,0,0,0,0,0,0x4a,0,0,0,0};
    ChaCha20 chacha20(key, nonce, 1);
    byte data[] = "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.";

    byte expected[] = {
        0x6e, 0x2e, 0x35, 0x9a, 0x25, 0x68, 0xf9, 0x80, 0x41, 0xba, 0x07, 0x28, 0xdd, 0x0d, 0x69, 0x81,
        0xe9, 0x7e, 0x7a, 0xec, 0x1d, 0x43, 0x60, 0xc2, 0x0a, 0x27, 0xaf, 0xcc, 0xfd, 0x9f, 0xae, 0x0b,
        0xf9, 0x1b, 0x65, 0xc5, 0x52, 0x47, 0x33, 0xab, 0x8f, 0x59, 0x3d, 0xab, 0xcd, 0x62, 0xb3, 0x57,
        0x16, 0x39, 0xd6, 0x24, 0xe6, 0x51, 0x52, 0xab, 0x8f, 0x53, 0x0c, 0x35, 0x9f, 0x08, 0x61, 0xd8,
        0x07, 0xca, 0x0d, 0xbf, 0x50, 0x0d, 0x6a, 0x61, 0x56, 0xa3, 0x8e, 0x08, 0x8a, 0x22, 0xb6, 0x5e,
        0x52, 0xbc, 0x51, 0x4d, 0x16, 0xcc, 0xf8, 0x06, 0x81, 0x8c, 0xe9, 0x1a, 0xb7, 0x79, 0x37, 0x36,
        0x5a, 0xf9, 0x0b, 0xbf, 0x74, 0xa3, 0x5b, 0xe6, 0xb4, 0x0b, 0x8e, 0xed, 0xf2, 0x78, 0x5e, 0x42,
        0x87, 0x4d
    };

    uint32 l = strlen((char*)data);
    chacha20.chacha20_cipher(data, l);

    for(size_t i=0; i< l; i++)
    {
        std::cout << HEX(data[i]) << " ";
        if(data[i] != expected[i])
        {
            std::cout << "\nError at position " << i << ": expected " << HEX(expected[i]) <<
                ", got " << HEX((data[i])) << ".\n";
            exit(EXIT_FAILURE);
        }
    }
    std::cout << "\n" << chacha20 << std::endl;
    std::cout << "\nSuccess!" << std::endl;
    return 0;
}
