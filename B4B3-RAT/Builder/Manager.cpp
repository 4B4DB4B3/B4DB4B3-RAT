#include "Manager.h"

std::string RandomStr(int len) {
	std::string tmp_s;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	srand((unsigned)time(NULL));

	for (int i = 0; i < len; ++i)
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

	return tmp_s;
}

std::string EncryptStr(std::string text, std::string key) {
	byte bKey[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memcpy(bKey, key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	std::string result = "";

	CryptoPP::AES::Encryption aesEncryption(bKey, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Encryption ebcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(ebcEncryption, new CryptoPP::StringSink(result));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.length() + 1);
	stfEncryptor.MessageEnd();

	return result;
}