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

#pragma once
#ifndef BUILDER_H
#define BUILDER_H
#include "common.h"

namespace Builder {
	#pragma pack(push, 1)
	struct Settings {
		char botapi[128] = { 0 };
		char key[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0 };

		char chatid[128] = { 0 };
		char drop[128] = { 0 };
		bool drop_run;

		char scheduler_name[50] = { 0 };
		bool scheduler_state;

		char autorun[128] = { 0 };
		bool autorun_state;

		char client_delay[10] = { 0 };
		bool auto_delete;

		bool protector;
		char protectorName[50] = { 0 };
	};
	#pragma pack(pop)

	BOOL MakeFile(const char* stub, const char* output, Settings*);
}

#endif