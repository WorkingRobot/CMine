#pragma once

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include "ConnEncrInfo.h"
#include "../packets/login/Packets.h"

#include <memory>
#include <unordered_map>

typedef ConnEncrInfo* ENC_CTX;

class ServerEnc {
public:
	ServerEnc();
	~ServerEnc();

	ENC_CTX GetEncrReq(CBEncrReq& req);
	bool HandleEncrResp(const ENC_CTX context, const SBEncrResp& resp);

	bool EncryptData(const ENC_CTX context, const char* input, int inputSize, char* output, int* outputSize);
	bool DecryptData(const ENC_CTX context, const char* input, int inputSize, char* output, int* outputSize);

	bool Disconnect(ENC_CTX context);

private:
	ENC_CTX GenerateConnection();

	int PublicKeySize;
	std::unique_ptr<char[]> PublicKey;

	std::vector<std::unique_ptr<ConnEncrInfo>> Connections;

	RSA* Rsa;
};