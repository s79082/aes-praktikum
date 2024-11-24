#include "aes.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>


// S-Box und Inverse S-Box

static const uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
    0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
    0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
    0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
    0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
    0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
    0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
    0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
    0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
    0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
    0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
    0xb0, 0x54, 0xbb, 0x16 };

static const uint8_t rsbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e,
    0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
    0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b, 0x94, 0x32,
    0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49,
    0x6d, 0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c, 0x70, 0x48, 0x50,
    0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05,
    0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
    0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91, 0x11, 0x41,
    0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8,
    0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
    0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b,
    0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59,
    0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
    0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d,
    0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63,
    0x55, 0x21, 0x0c, 0x7d };


void keyExpansion(u_int8_t* key, u_int8_t* roundKeys, unsigned int keySize) {
    u_int8_t Nk = numKeyWords(keySize);
    u_int8_t Nr = numRounds(keySize);
    u_int8_t keyLength = 4 * (Nr + 1);

    memcpy(roundKeys, key, Nk * 4);
    for (unsigned int i = Nk; i < keyLength; ++i) {
        u_int8_t temp[4];
        memcpy(temp, &roundKeys[(i - 1) * 4], 4);

        if (i % Nk == 0) {
            // RotWord, SubWord, Rcon
            u_int8_t t = temp[0];
            temp[0] = getSBoxValue(temp[1]) ^ rc(i / Nk);
            temp[1] = getSBoxValue(temp[2]);
            temp[2] = getSBoxValue(temp[3]);
            temp[3] = getSBoxValue(t);
        } else if (Nk > 6 && i % Nk == 4) {
            temp[0] = getSBoxValue(temp[0]);
            temp[1] = getSBoxValue(temp[1]);
            temp[2] = getSBoxValue(temp[2]);
            temp[3] = getSBoxValue(temp[3]);
        }
        for (u_int8_t j = 0; j < 4; ++j) {
            roundKeys[i * 4 + j] = roundKeys[(i - Nk) * 4 + j] ^ temp[j];
        }
    }
 /*   unsigned int Nk = keySize / 4;  // Number of 32-bit words in the key
    unsigned int Nb = 4;           // Number of 32-bit words in the block
    unsigned int N = numKeys(keySize); // Number of rounds
    unsigned int R = numRounds(keySize);
    unsigned int i, j;
    uint8_t temp[4];


    for (i = 0; i < Nb * R; i++) {
        if (i < N) {
            roundKeys[i] = key;
            continue;
        }
        if (i >= N && i % N == 0) {
            key[i - N] ^ subBytes(shiftRows())
        }
    }

    // Copy the initial key into the first Nk words of the roundKeys
    memcpy(roundKeys, key, Nk * 4);

    // Generate the rest of the round keys
    for (i = Nk; i < Nb * (Nr + 1); i++) {
        memcpy(temp, &roundKeys[(i - 1) * 4], 4);

        // Perform the key schedule core every Nk words
        if (i % Nk == 0) {
            // Rotate left
            uint8_t t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            // SubBytes (apply S-box)
            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];

            // Add the round constant
            temp[0] ^= Rcon[i / Nk];
        } else if (Nk > 6 && i % Nk == 4) {
            // For AES-256, every 4th word undergoes the S-box substitution
            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];
        }

        // XOR with the word Nk positions earlier
        for (j = 0; j < 4; j++) {
            roundKeys[i * 4 + j] = roundKeys[(i - Nk) * 4 + j] ^ temp[j];
        }
    }*/
}


unsigned int numRounds(unsigned int keySize) {
    switch(keySize) {
        case 128: return 10;
        case 192: return 12;
        case 256: return 14;
        default: return -1;
    }
}

unsigned int numKeyWords(unsigned int keySize) {
    switch (keySize) {
        case 128: return 4;
        case 192: return 6;
        case 256: return 8;
        default: return -1;  // Ungültige Schlüssellänge
    }
}

u_int8_t getSBoxValue(u_int8_t num) { 
    return sbox[num];
    }

u_int8_t getSBoxInvert(u_int8_t num) { 
    return rsbox[num];
    
}
static const uint8_t rcon[256] = {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, /* weitere Werte */
    };
u_int8_t rc(u_int8_t num) {
        return rcon[num - 1];
}


void getRoundKey(u_int8_t* roundKeys, u_int8_t* roundKey, u_int8_t round) {

    memcpy(roundKey, &roundKeys[round * 16], 16);
}

void addRoundKey(u_int8_t* state, u_int8_t* roundKey) {

    for (int i = 0; i < 16; ++i) {
        state[i] ^= roundKey[i];
    }
}

void subBytes(u_int8_t* state) {
    for (int i = 0; i < 16; ++i) {
        state[i] = getSBoxValue(state[i]);
    }
}

void shiftRows(u_int8_t* state) {
    uint8_t temp;

    // Row 1: Shift 1 position to the left
    temp = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = temp;

    // Row 2: Shift 2 positions to the left
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Row 3: Shift 3 positions to the left (equivalent to shifting 1 position to the right)
    temp = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = state[3];
    state[3] = temp;
}

void multiply2(uint8_t* state) {
    for (int i = 0; i < 16; i++) {
        // Check if the most significant bit is 1
        uint8_t msb = (state[i] & 0x80) ? 0x1b : 0x00;
        // Left shift by 1 and XOR with the constant if MSB was 1
        state[i] = (state[i] << 1) ^ msb;
    }
}

void multiply3(uint8_t* state) {
    uint8_t temp[16];
    for (int i = 0; i < 16; i++) {
        temp[i] = state[i];  // Preserve the original state for addition
    }

    multiply2(state);  // Compute multiplication by 2
    for (int i = 0; i < 16; i++) {
        state[i] ^= temp[i];  // Add (XOR) the original value to get multiplication by 3
    }
}

void mixColumns(u_int8_t* state) {

    for (int c = 0; c < 4; ++c) {
        u_int8_t a[4], b[4];
        for (int i = 0; i < 4; ++i) {
            a[i] = state[c * 4 + i];
            b[i] = (state[c * 4 + i] << 1) ^ ((state[c * 4 + i] & 0x80) ? 0x1b : 0x00);
        }
        state[c * 4 + 0] = b[0] ^ a[1] ^ b[1] ^ a[2] ^ a[3];
        state[c * 4 + 1] = a[0] ^ b[1] ^ a[2] ^ b[2] ^ a[3];
        state[c * 4 + 2] = a[0] ^ a[1] ^ b[2] ^ a[3] ^ b[3];
        state[c * 4 + 3] = a[0] ^ b[0] ^ a[1] ^ a[2] ^ b[3];
    }
}
uint8_t gf_multiply(uint8_t a, uint8_t b) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        uint8_t high_bit = a & 0x80;
        a <<= 1;
        if (high_bit) {
            a ^= 0x1b; // AES irreducible polynomial
        }
        b >>= 1;
    }
    return result;
}
void invMixColumns(u_int8_t* state) {
    uint8_t tempState[16];

    for (int col = 0; col < 4; col++) {
        uint8_t a0 = state[col * 4 + 0];
        uint8_t a1 = state[col * 4 + 1];
        uint8_t a2 = state[col * 4 + 2];
        uint8_t a3 = state[col * 4 + 3];

        tempState[col * 4 + 0] = gf_multiply(a0, 0x0e) ^ gf_multiply(a1, 0x0b) ^
                                 gf_multiply(a2, 0x0d) ^ gf_multiply(a3, 0x09);
        tempState[col * 4 + 1] = gf_multiply(a0, 0x09) ^ gf_multiply(a1, 0x0e) ^
                                 gf_multiply(a2, 0x0b) ^ gf_multiply(a3, 0x0d);
        tempState[col * 4 + 2] = gf_multiply(a0, 0x0d) ^ gf_multiply(a1, 0x09) ^
                                 gf_multiply(a2, 0x0e) ^ gf_multiply(a3, 0x0b);
        tempState[col * 4 + 3] = gf_multiply(a0, 0x0b) ^ gf_multiply(a1, 0x0d) ^
                                 gf_multiply(a2, 0x09) ^ gf_multiply(a3, 0x0e);
    }

    for (int i = 0; i < 16; i++) {
        state[i] = tempState[i];
    }
}

void printBlock(u_int8_t* block) {
}

void encrypt(u_int8_t* block, u_int8_t* roundKeys, unsigned int rounds) {
    addRoundKey(block, roundKeys);
    for (unsigned int i = 1; i < rounds; ++i) {
        subBytes(block);
        shiftRows(block);
        mixColumns(block);
        addRoundKey(block, &roundKeys[i * 16]);
    }
    subBytes(block);
    shiftRows(block);
    addRoundKey(block, &roundKeys[rounds * 16]);
}

void invSubBytes(u_int8_t* state) {
     for (int i = 0; i < 16; ++i) {
        state[i] = getSBoxInvert(state[i]);
    }
}

void invShiftRows(u_int8_t *state) {
    uint8_t temp[16];
    memcpy(temp, state, 16);

    state[1] = temp[13]; state[5] = temp[1];  state[9] = temp[5];  state[13] = temp[9];
    state[2] = temp[10]; state[6] = temp[14]; state[10] = temp[2]; state[14] = temp[6];
    state[3] = temp[7];  state[7] = temp[11]; state[11] = temp[15]; state[15] = temp[3];
}

void decrypt(u_int8_t* block, u_int8_t* roundKeys, unsigned int rounds) {
    addRoundKey(block, &roundKeys[rounds * 16]);
    for (unsigned int i = rounds - 1; i > 0; --i) {
        invShiftRows(block);
        invSubBytes(block);
        addRoundKey(block, &roundKeys[i * 16]);
        invMixColumns(block);
    }
    invShiftRows(block);
    invSubBytes(block);
    addRoundKey(block, roundKeys);
}

void ecb_encrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, size_t length){
    unsigned int rounds = numRounds(keySize);
    uint8_t roundKeys[240];  // Maximal für AES-256
    keyExpansion(key, roundKeys, keySize);

    for (size_t i = 0; i < length; i += 16) {
        encrypt(&content[i], roundKeys, rounds);
    }
}

void ecb_decrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, size_t length){

    unsigned int rounds = numRounds(keySize);
    uint8_t roundKeys[240];
    keyExpansion(key, roundKeys, keySize);

    for (size_t i = 0; i < length; i += 16) {
        decrypt(&content[i], roundKeys, rounds);
    }
}


void cbc_encrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, u_int8_t *iv, size_t length) {
 unsigned int rounds = numRounds(keySize);
    uint8_t roundKeys[240];
    uint8_t buffer[16];

    keyExpansion(key, roundKeys, keySize);
    memcpy(buffer, iv, 16);

    for (size_t i = 0; i < length; i += 16) {
        for (int j = 0; j < 16; ++j) {
            content[i + j] ^= buffer[j];
        }
        encrypt(&content[i], roundKeys, rounds);
        memcpy(buffer, &content[i], 16);
    }
}

void cbc_decrypt(u_int8_t *content, u_int8_t *key, unsigned int keySize, u_int8_t *iv, size_t length) {
unsigned int rounds = numRounds(keySize);
    uint8_t roundKeys[240];
    uint8_t buffer[16], temp[16];

    keyExpansion(key, roundKeys, keySize);
    memcpy(buffer, iv, 16);

    for (size_t i = 0; i < length; i += 16) {
        memcpy(temp, &content[i], 16);
        decrypt(&content[i], roundKeys, rounds);
        for (int j = 0; j < 16; ++j) {
            content[i + j] ^= buffer[j];
        }
        memcpy(buffer, temp, 16);
    }
}
