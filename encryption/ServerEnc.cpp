#include "ServerEnc.h"

ServerEnc::ServerEnc() {
	auto bn = BN_new();
	if (!BN_set_word(bn, RSA_F4)) {

	}
	Rsa = RSA_new();
	if (!RSA_generate_key_ex(Rsa, 1024, bn, NULL)) {
		
	}
	BN_free(bn);

	auto bio = BIO_new(BIO_s_mem());

	if (!i2d_RSA_PUBKEY_bio(bio, Rsa)) {

	}

	BUF_MEM* bptr;
	BIO_get_mem_ptr(bio, &bptr);

	PublicKey = std::make_unique<char[]>(bptr->length);
	memcpy(PublicKey.get(), bptr->data, bptr->length);

	BIO_set_close(bio, BIO_CLOSE);
	BIO_free(bio);
}

ServerEnc::~ServerEnc() {
	RSA_free(Rsa);
}

ENC_CTX ServerEnc::GetEncrReq(CBEncrReq& req) {
	auto conn = GenerateConnection();

	req.PublicKeyLen = PublicKeySize;
	req.PublicKey = std::make_unique<char[]>(PublicKeySize);
	memcpy(req.PublicKey.get(), PublicKey.get(), PublicKeySize);

	req.VerifyKeyLen = 4;
	req.VerifyKey = std::make_unique<char[]>(4);
	memcpy(req.VerifyKey.get(), conn->VerifyToken, 4);

	// req.ServerID should do something here but it should be empty, idk

	return conn;
}

bool ServerEnc::HandleEncrResp(const ENC_CTX context, const SBEncrResp& resp) {
	char DecrVerify[4];
	if (!RSA_private_decrypt(resp.VerifyTokenLen.Value, (unsigned char*)resp.VerifyToken.get(), (unsigned char*)DecrVerify, Rsa, RSA_PKCS1_PADDING)) {

	}
	if (memcmp(DecrVerify, context->VerifyToken, 4)) {

	}

	char SharedSecret[16];
	if (!RSA_private_decrypt(resp.SharedSecretLen.Value, (unsigned char*)resp.SharedSecret.get(), (unsigned char*)SharedSecret, Rsa, RSA_PKCS1_PADDING)) {

	}

	context->EncCipher = EVP_CIPHER_CTX_new();
	context->DecCipher = EVP_CIPHER_CTX_new();

	if (!EVP_CipherInit_ex(context->EncCipher, EVP_aes_128_cfb8(), NULL, (unsigned char*)SharedSecret, (unsigned char*)SharedSecret, 1)) {

	}
	if (!EVP_CipherInit_ex(context->DecCipher, EVP_aes_128_cfb8(), NULL, (unsigned char*)SharedSecret, (unsigned char*)SharedSecret, 0)) {

	}

	return true;
}

bool ServerEnc::EncryptData(const ENC_CTX context, const char* input, int inputSize, char* output, int* outputSize)
{
	return EVP_CipherUpdate(context->EncCipher, (unsigned char*)output, outputSize, (unsigned char*)input, inputSize);
}

bool ServerEnc::DecryptData(const ENC_CTX context, const char* input, int inputSize, char* output, int* outputSize)
{
	return EVP_CipherUpdate(context->DecCipher, (unsigned char*)output, outputSize, (unsigned char*)input, inputSize);
}

bool ServerEnc::Disconnect(ENC_CTX context)
{
	auto p = std::find_if(Connections.begin(), Connections.end(), [context](const std::unique_ptr<ConnEncrInfo>& n) { return context == n.get(); });
	if (p != Connections.end()) {
		Connections.erase(p);
		return true;
	}
	return false;
}

ENC_CTX ServerEnc::GenerateConnection()
{
	auto& conn = Connections.emplace_back(std::make_unique<ConnEncrInfo>());
	if (!RAND_bytes((unsigned char*)conn->VerifyToken, 4)) {

	}
	return conn.get();
}
