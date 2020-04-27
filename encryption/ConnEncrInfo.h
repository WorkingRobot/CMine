#pragma once

#include <openssl/evp.h>

struct ConnEncrInfo {
	char VerifyToken[4];

	EVP_CIPHER_CTX* EncCipher;
	EVP_CIPHER_CTX* DecCipher;
};