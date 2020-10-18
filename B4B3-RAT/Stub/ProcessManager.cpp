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

#include "ProcessManager.h"

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

bool CloseProcess(std::string procname) {
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

bool InjectDLL(const char* procname, const char* dllname) {
	DWORD PID = PIDByName(procname);
	if (PID == 0)
		return false;

	HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	LPVOID DllAddr = VirtualAllocEx(h_process, NULL, _MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);  
	if (DllAddr == NULL)
		return 0;

	if (!(WriteProcessMemory(h_process, DllAddr, dllname, strlen(dllname), NULL)))
		return false;

	LPVOID LoadLibA = GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");                   
	if (LoadLibA == NULL)
		return false;

	HANDLE hThread = CreateRemoteThread(h_process, NULL, 0,                     
		(LPTHREAD_START_ROUTINE)LoadLibA, DllAddr, 0, NULL);
	if (hThread == NULL)
		return false;

	WaitForSingleObject(hThread, INFINITE);

	DWORD exit_code;
	GetExitCodeThread(hThread, &exit_code);											

	CloseHandle(hThread);
	VirtualFreeEx(h_process, DllAddr, 0, MEM_RELEASE);
	CloseHandle(h_process);                                                    

	return true;
}

DWORD PIDByName(std::string name) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != NULL) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &pe32)) {
			do {
				if (strcmp(pe32.szExeFile, name.c_str()) == 0) {
					return pe32.th32ProcessID;
				}
			} while (Process32Next(hSnap, &pe32));
		}
	}
	return 0;
}