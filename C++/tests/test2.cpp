#include "../src/ChaCha20.h"
#include <stdio.h>

#define OUT_FILE argc<4? "output.out": argv[3]

int main(int argc, char const *argv[])
{
    FILE* keyFile = fopen(argv[2], "rb");
    if(!keyFile)
    {
        printf("%s: key file not found.", argv[2]);
        exit(EXIT_FAILURE);
    }
    byte key[KEY_SIZE];
    fread(key, sizeof(byte), KEY_SIZE, keyFile);
    byte nonce[NONCE_SIZE] = {0,0,0,0,0,0,0,0x4a,0,0,0,0};
    
    FILE* dataFile = fopen(argv[1], "rb");
    FILE* out = fopen(OUT_FILE, "wb");
    if(!dataFile)
    {
        printf("Failed to open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    else if(!out)
    {
        printf("Failed to open %s\n", OUT_FILE);
    }
    byte buffer[STATE_BUFFER_SIZE];
    uint32 n;
    ChaCha20 chacha20(key, nonce, 1);
    do
    {
        n = fread(buffer, sizeof(byte), STATE_BUFFER_SIZE, dataFile);
        chacha20.chacha20_cipher(buffer, n);
        fwrite(buffer, sizeof(byte), n, out);
    } while (n);
    
    fclose(keyFile);
    fclose(dataFile);
    fclose(out);
    return 0;
}