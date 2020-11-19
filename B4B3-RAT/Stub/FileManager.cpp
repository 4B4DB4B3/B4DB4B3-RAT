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

#include "FileManager.h"

std::string FileManager::DirectoryObjectsList(std::string dir) {
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

std::string FileManager::ReadFile(std::string path) {
	std::string text = "";

	std::ifstream file(path);
	if (file.is_open()) {
		std::string tmp = "";
		while (std::getline(file, tmp)) {
			text += tmp;
		}
		file.close();
	}
	
	return text;
}

BOOL FileManager::WriteFile(std::string path, std::string text) {
	std::ofstream file(path);
	if (file.is_open()) {
		file << text;
		file.close();

		return TRUE;
	}

	return FALSE;
}