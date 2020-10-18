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

#include "Information.h"
#include "Requests.h"

std::string GetOS() {
    OSVERSIONINFO vi;
    vi.dwOSVersionInfoSize = sizeof(vi);
    if (GetVersionEx(&vi) == 0) 
        return "Error getting ";
	
	if (vi.dwMajorVersion == 10 && vi.dwMinorVersion == 0) {
		return "Windows 10";
	}
	else if (vi.dwMajorVersion == 6 && vi.dwMinorVersion == 3) {
		return "Windows 8.1";
	}
	else if (vi.dwMajorVersion == 6 && vi.dwMinorVersion == 2) {
		return "Windows 8";
	}
	else if (vi.dwMajorVersion == 6 && vi.dwMinorVersion == 1) {
		return "Windows 7";
	}
	else if (vi.dwMajorVersion == 6 && vi.dwMinorVersion == 0) {
		return "Windows Vista";
	}
	else if (vi.dwMajorVersion == 5 && vi.dwMinorVersion == 1) {
		return "Windows XP";
	}
	else if (vi.dwMajorVersion == 5 && vi.dwMinorVersion == 0) {
		return "Windows 2000";
	}
	else {
		return "Unknown OS";
	}
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

std::string GetProcessorBrand() {
	int CPUInfo[4] = { -1 };

	__cpuidex(CPUInfo, 0x80000000, 0);
	unsigned int index = CPUInfo[0];

	char ProcessorBrand[0x40] = { 0 };

	for (unsigned int i = 0x80000000; i <= index; ++i)
	{
		__cpuidex(CPUInfo, i, 0);

		switch (i) {
		case 0x80000002:
			memcpy(ProcessorBrand, CPUInfo, sizeof(CPUInfo));
			break;

		case 0x80000003:
			memcpy(ProcessorBrand + 16, CPUInfo, sizeof(CPUInfo));
			break;

		case 0x80000004:
			memcpy(ProcessorBrand + 32, CPUInfo, sizeof(CPUInfo));
			break;

		default:
			break;
		}
	}

	return ProcessorBrand;
}