#include <stdio.h>
#include "../src/ChaCha20.h"

// reads and encrypts the file which name is argv[1]
int main(int argc, char const *argv[])
{

    FILE* input = fopen(argv[1], "rb");
    if(!input) exit(1);

    FILE* outFile = fopen(argv[2], "wb");
    if(!outFile) outFile = fopen("result.out", "wb");

    byte key[KEY_SIZE];
    for (int i = 0; i < 32; i++)
        key[i] = i;
    byte nonce[NONCE_SIZE] = {0x79, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x74};
    uint32 counter = 0;
    byte buffer[STATE_BUFFER_SIZE];
    size_t n;
    do
    {
        n = fread(buffer, 1, STATE_BUFFER_SIZE, input);
        chacha20_cipher(key, counter++, nonce, buffer, n);
        fwrite(buffer, 1, n, outFile);
    } while (n);
    

    return 0;
}
