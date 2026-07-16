package krypt

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func RC4Crypt(data []byte, key []byte) ([]byte, error) {
	return AESGCMDecrypt(data, key)
}

func AESGCMEncrypt(plaintext []byte, key []byte) ([]byte, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, errors.New("aes cipher error")
	}

	aesgcm, err := cipher.NewGCM(block)
	if err != nil {
		return nil, errors.New("aes gcm error")
	}

	nonce := make([]byte, aesgcm.NonceSize())
	if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
		return nil, errors.New("nonce generation error")
	}

	ciphertext := aesgcm.Seal(nonce, nonce, plaintext, nil)
	return ciphertext, nil
}

func AESGCMDecrypt(ciphertext []byte, key []byte) ([]byte, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, errors.New("aes cipher error")
	}

	aesgcm, err := cipher.NewGCM(block)
	if err != nil {
		return nil, errors.New("aes gcm error")
	}

	nonceSize := aesgcm.NonceSize()
	if len(ciphertext) < nonceSize {
		return nil, errors.New("ciphertext too short")
	}

	nonce, cipherdata := ciphertext[:nonceSize], ciphertext[nonceSize:]
	plaintext, err := aesgcm.Open(nil, nonce, cipherdata, nil)
	if err != nil {
		return nil, errors.New("aes gcm decrypt error")
	}

	return plaintext, nil
}
