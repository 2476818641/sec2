#pragma once

#define AES_BLOCK_SIZE 16
#define AES128_KEY_SIZE 16
#define GCM_NONCE_SIZE 12
#define GCM_TAG_SIZE   16

void AESGCMEncrypt(const unsigned char* plaintext, int plainLen,
                   const unsigned char* key, unsigned char* nonceOut,
                   unsigned char* ciphertext, unsigned char* tagOut);

int AESGCMDecrypt(const unsigned char* ciphertext, int cipherLen,
                  const unsigned char* key, const unsigned char* nonce,
                  unsigned char* plaintext, const unsigned char* tag);

void RC4Init(unsigned char* key, unsigned char* S, int keyLength);

void RC4EncryptDecrypt(unsigned char* data, int dataLength, unsigned char* S);

void EncryptRC4(unsigned char* data, int dataLength, unsigned char* key, int keyLength);

void DecryptRC4(unsigned char* data, int dataLength, unsigned char* key, int keyLength);
