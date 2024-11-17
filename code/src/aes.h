#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

unsigned int numRounds(unsigned int keySize);

unsigned int numKeyWords(unsigned int keySize);

u_int8_t getSBoxValue(u_int8_t num);

u_int8_t getSBoxInvert(u_int8_t num);

u_int8_t rc(u_int8_t num);

void keyExpansion(u_int8_t* key, u_int8_t* roundKeys, unsigned int keySize);

void getRoundKey(u_int8_t* roundKeys, u_int8_t* roundKey, u_int8_t round);

void addRoundKey(u_int8_t* state, u_int8_t* roundKey);

void subBytes(u_int8_t* state);

void shiftRows(u_int8_t* state);

void multiply2(u_int8_t* state);

void multiply3(u_int8_t* state);

void mixColumns(u_int8_t *state);

void encrypt(u_int8_t* block, u_int8_t* roundKeys, unsigned int rounds);

void invMixColumns(u_int8_t* state);

void invSubBytes(u_int8_t* state);

void invShiftRows(u_int8_t* state);

void decrypt(u_int8_t* block, u_int8_t* roundKeys, unsigned int rounds);

void ecb_encrypt (u_int8_t* content, u_int8_t* key, unsigned int keySize, size_t length);

void ecb_decrypt (u_int8_t* content, u_int8_t* key, unsigned int keySize, size_t length);

void cbc_encrypt (u_int8_t* content, u_int8_t* key, unsigned int keySize, u_int8_t* iv, size_t length);

void cbc_decrypt (u_int8_t* content, u_int8_t* key, unsigned int keySize, u_int8_t* iv, size_t length);