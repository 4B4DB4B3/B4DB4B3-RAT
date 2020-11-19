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

#include "Protector.h"
#include "Manager.h"
#include <winternl.h>

void Protector::AntiProcesses() {
	HANDLE hSnap;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	std::vector<std::string> processes =
	{
		"ollydbg.exe",
		"ProcessHacker.exe",
		"tcpview.exe",
		"autoruns.exe",
		"autorunsc.exe",
		"filemon.exe",
		"procmon.exe",
		"regmon.exe",
		"procexp.exe",
		"idaq.exe",
		"idaq64.exe",
		"ImmunityDebugger.exe",
		"Wireshark.exe",
		"dumpcap.exe",
		"HookExplorer.exe",
		"ImportREC.exe",
		"PETools.exe",
		"LordPE.exe",
		"SysInspector.exe",
		"proc_analyzer.exe",
		"sysAnalyzer.exe",
		"sniff_hit.exe",
		"windbg.exe",
		"joeboxcontrol.exe",
		"joeboxserver.exe"
	};

	std::string process = "";
	while (true) {
		Sleep(3000);
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap != NULL) {
			if (Process32First(hSnap, &pe32)) {
				do {
					process = Manager::ToLower(pe32.szExeFile);
					for (size_t i = 0; i < processes.size(); i++) {
						if (process.find(processes[i]) != std::string::npos) {
							ExitProcess(0);
						}
					}
				} while (Process32Next(hSnap, &pe32));
			}
		}
	}
}