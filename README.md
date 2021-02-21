# ChaCha20
A C implementation of the ChaCha20 encryption scheme

## ChaCHa20.h

Contains all the required macros and function definitions.

### Macros and types

- `KEY_SIZE`: The ChaCha20 key size, in bytes := 32
- `NONCE_SIZE`: The ChaCha20 nonce size in bytes := 12
- `STATE_BUFFER_SIZE`: The ChaCha20 state buffer size in bytes := 64
- `uint32`: Represents a 32-bit unsigned integer
- `byte`: represents an 8-bit unsigned integer
- `R(x, n)`: The rotation of x (`uint32`) by n bits to the left
- `LITTLE_ENDIAN(b)`: The conversion of b (`byte[4]`) to a little endian `uint32` integer

### Functions

```C
void chacha20_block(byte* key, uint32 counter, byte* nonce, byte* output)
```
Sets up the state matrix from the key, nonce and block counter, hashes it and copies the 64-byte result into the output buffer.

```C
void chacha20_cipher(byte key[KEY_SIZE], uint32 counter, byte nonce[NONCE_SIZE], byte input[STATE_BUFFER_SIZE], uint32 n)
```
Encrypts the n-byte input buffer by XORing it with the ChaCha20 keystream. If n>64, the function will only encrypt 64 bytes.