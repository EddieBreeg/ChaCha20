#include "ChaCha20.h"

ChaCha20::ChaCha20(byte* key, byte* nonce, uint32 blockCounter)
{
    this->blockCounter = blockCounter;
    _initState = new uint32[16]{
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
        0,0,0,0,
        0,0,0,0,
        blockCounter, 0,0,0
    };
    for (size_t i = 0; i < 8; i++)
        _initState[4+i] = LITTLE_ENDIAN((key+4*i));
    for(int i=0; i<3; i++)
        _initState[13+i] = LITTLE_ENDIAN((nonce+4*i));

    _output = new byte[STATE_BUFFER_SIZE]{0};
}
const uint32 ChaCha20::operator[](int i){ return _output[i]; }
ChaCha20::~ChaCha20()
{
    delete _output;
    delete _initState;
}
void quarterRound(uint32& a, uint32& b, uint32& c, uint32& d)
{
    a += b; d ^= a; d = R(d, 16);
    c += d; b ^= c; b = R(b, 12);
    a += b; d ^= a; d = R(d, 8);
    c += d; b ^= c; b = R(b, 7);
}
void innerBlock(uint32 state[16])
{
    quarterRound(state[0], state[4], state[8],  state[12]);
    quarterRound(state[1], state[5], state[9],  state[13]);
    quarterRound(state[2], state[6], state[10], state[14]);
    quarterRound(state[3], state[7], state[11], state[15]);
    quarterRound(state[0], state[5], state[10], state[15]);
    quarterRound(state[1], state[6], state[11], state[12]);
    quarterRound(state[2], state[7], state[8],  state[13]);
    quarterRound(state[3], state[4], state[9],  state[14]);
}
void ChaCha20::block(void)
{
    uint32 state[16];
    _initState[12] = blockCounter;
    memcpy(state, _initState, STATE_BUFFER_SIZE);
    for(int i=0; i<10; i++)
        innerBlock(state);
    for(int i = 0; i < 16; i++)
        state[i] += _initState[i];
    for (int i = 0; i < 16; i++)
    {
        byte* d = _output + 4*i;
        for (int j = 0; j < 4; j++)
        {
            d[j] = state[i] & 0xff;
            state[i] >>= 8;
        }
    }
}
void ChaCha20::block(uint32 counter)
{
    blockCounter = counter;
    block();
}
void ChaCha20::chacha20_cipher(byte data[], uint32 n)
{
    block();
    for(size_t i=0; i< (n<STATE_BUFFER_SIZE?n:STATE_BUFFER_SIZE); i++)
        data[i] ^= _output[i];
    blockCounter++;
}